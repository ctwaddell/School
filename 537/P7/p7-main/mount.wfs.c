/*
mount.wfs.c
This program mounts the filesystem to a mount point, which are specifed by the
arguments. The usage is mount.wfs [FUSE options] disk_path mount_point You need
to pass [FUSE options] along with the mount_point to fuse_main as argv. You may
assume -s is always passed to mount.wfs as a FUSE option to disable
multi-threading.
*/

#define FUSE_USE_VERSION 30

#include <errno.h>
#include <fuse.h>
#include <fuse/fuse_common.h>
#include <linux/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#include "fcntl.h"
#include "wfs.h"

int writeflag = 0;

/*
 * LOG ENTRY FUNCTIONS
 */

struct wfs_log_entry* get_log_entry(unsigned int inode) {
    struct wfs_log_entry* entry = get_first_entry();
    void* start_ptr = (void*)entry;
    void* work_ptr = (void*)start_ptr;
    struct wfs_sb* sb = get_sb();
    struct wfs_log_entry* latest = NULL;
    void* max_ptr =
        (void*)(((unsigned long)get_sb()) + (unsigned long)sb->head);
    // printf("start: %p\t max: %p\n", work_ptr, max_ptr);

    while ((unsigned long)work_ptr < (unsigned long)max_ptr) {
        struct wfs_log_entry* cur_entry = work_ptr;
        //  //   printf("cur_entry: %d\t at %p \t need: %d\n",
        //            (int)cur_entry->inode.inode_number, (void*)cur_entry,
        //            (int)inode);
        if (cur_entry->inode.inode_number == inode &&
            cur_entry->inode.deleted == 0) {
            latest = cur_entry;
        }

        // go next
        unsigned long a = (unsigned long)work_ptr;
        work_ptr =
            (void*)(a + cur_entry->inode.size + sizeof(struct wfs_log_entry));
        // work_ptr += sizeof(struct wfs_log_entry) + entry->inode.size;
    }

   // printf("start: %p\t end: %p\n", start_ptr, (void*)latest);
    //    print_inode(latest);

    return latest;
}

struct wfs_dentry* search_entry_for_name(struct wfs_log_entry* entry,
                                         char* name) {
    int num_entries = entry->inode.size / sizeof(struct wfs_dentry);

    //printf("num_entries: %d\n", num_entries);

    unsigned long base = (unsigned long)entry->data;
    for (int i = 0; i < num_entries; i++) {
        void* ptr = (void*)(base + i * sizeof(struct wfs_dentry));

        struct wfs_dentry* dentry = (struct wfs_dentry*)ptr;
       // printf("dentry: %s\n", dentry->name);

        if (strncmp(dentry->name, name, strlen(dentry->name)) == 0) {
            return dentry;
        }
    }

    return NULL;
}

void* get_head() {
    char* address = start_disk;
    struct wfs_sb* superblock = get_sb();
    address += superblock->head;
    return (void*)address;
}

/*
 * INODE FUNCTIONS
 */

void print_inode(struct wfs_inode* inode) {
    printf(
        "inode: [inode_number: %u, deleted: %u, mode: %u, uid: %u, gid: %u, "
        "flags: %u, size: %u, atime: %u, mtime: %u, ctime: %u, links: %u]\n",
        inode->inode_number, inode->deleted, inode->mode, inode->uid,
        inode->gid, inode->flags, inode->size, inode->atime, inode->mtime,
        inode->ctime, inode->links);
}

struct wfs_inode create_inode(unsigned int inode_number, unsigned int deleted,
                              unsigned int mode, unsigned int uid,
                              unsigned int gid, unsigned int flags,
                              unsigned int size, unsigned int atime,
                              unsigned int mtime, unsigned int ctime,
                              unsigned int links) {
    struct wfs_inode inode;

    inode.inode_number = inode_number;
    inode.deleted = deleted;
    inode.mode = mode;
    inode.uid = uid;
    inode.gid = gid;
    inode.flags = flags;
    inode.size = size;
    inode.atime = atime;
    inode.mtime = mtime;
    inode.ctime = ctime;
    inode.links = links;

    return inode;
}

struct wfs_inode* find_inode(unsigned int inode) {
    struct wfs_log_entry* entry = get_first_entry();
    void* start_ptr = (void*)entry;
    void* work_ptr = (void*)start_ptr;
    // print_inode(&entry->inode);
    struct wfs_sb* sb = get_sb();
    struct wfs_inode* latest = NULL;
    void* max_ptr =
        (void*)(((unsigned long)get_sb()) + (unsigned long)sb->head);
    //printf("start: %p\t max: %p\n", work_ptr, max_ptr);

    while ((unsigned long)work_ptr < (unsigned long)max_ptr) {
        struct wfs_log_entry* cur_entry = work_ptr;
        // printf("cur_entry: %d\t at %p \t need: %d\n",
        if (cur_entry->inode.inode_number == inode &&
            cur_entry->inode.deleted == 0) {
            latest = &cur_entry->inode;
        }

        // go next
        unsigned long a = (unsigned long)work_ptr;
        work_ptr =
            (void*)(a + cur_entry->inode.size + sizeof(struct wfs_log_entry));
        // work_ptr += sizeof(struct wfs_log_entry) + entry->inode.size;
    }

    //printf("start: %p\t end: %p\n", start_ptr, (void*)latest);
    //print_inode(latest);
 
    return latest;
}

char* resolve_path(const char* path) {
    if (path == NULL) {
        return NULL;  // Invalid input
    }

    // Allocate memory for the resolved path
    char* resolved_path = (char*)malloc(512);
    if (resolved_path == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    // Initialize variables for tokenizationname
    char* token;
    char* rest = (char*)path;

    // Initialize stack to keep track of directories
    const int max_depth = 256;
    char* stack[max_depth];
    int depth = 0;

    // Tokenize the input path and process each component
    while ((token = strtok_r(rest, "/", &rest)) != NULL) {
        if (strcmp(token, ".") == 0) {
            // Ignore "." (current directory)
        } else if (strcmp(token, "..") == 0) {
            // Move up one level for ".." (parent directory)
            if (depth > 0) {
                depth--;
            }
        } else {
            // Add valid directory names to the stack
            if (depth < max_depth - 1) {
                stack[depth++] = token;
            } else {
                fprintf(stderr, "Path resolution error: Max depth reached\n");
                free(resolved_path);
                exit(EXIT_FAILURE);
            }
        }
    }

    // Construct the resolved path
    strcpy(resolved_path, "/");
    for (int i = 0; i < depth; ++i) {
        strcat(resolved_path, stack[i]);
        strcat(resolved_path, "/");
    }

    if (strncmp(&resolved_path[strlen(resolved_path) - 1], "/", 1) == 0 && strlen(resolved_path) != 0) {
        resolved_path[strlen(resolved_path) - 1] = '\0';
    }
    printf("str: %s\t len: %lu\n", resolved_path, strlen(resolved_path));
    
    return resolved_path;
}

int path_to_inode_number(char* relpath) {
    struct wfs_log_entry* entry = get_first_entry();
 
    //char* path = malloc(512);
    //char* rel = relpath + 1;

    char* path = resolve_path(++relpath);
    printf("PATH: %s\n", path);
    //strncpy(path, rel, strlen(rel));

   // printf("abspath: %s, relpath: %s, rel: %s\n", path, relpath, rel);


    unsigned long work_ptr = (unsigned long)entry;
    // print_inode(&entry->inode);

    char* name = strtok(path, "/");
    if (strcmp(path, "/") == 0) {
        //printf("root\n");
        return 0;
    }
    // name = strtok(NULL, "/");
    //printf("name: %s\n", name);

    
    if (name == NULL) {
       // printf("not root\n");
       // printf("name == null path: %s\n", path);
        return entry->inode.inode_number;
    }

    // if (strncmp(name, ".", 1) == 0) {
    //     name = strtok(NULL, "/");
    // }

    // if (strncmp(name, "..", 2) == 0) {
        
    // }
   // printf("name: %s, length: %d\n", name, (int)strlen(name));

    if (entry == NULL) {
        //printf("entry null\n");
    }

   
    struct wfs_sb* sb = get_sb();
    unsigned long max_ptr = (unsigned long)sb + (unsigned long)sb->head;

    while (work_ptr < max_ptr && name != NULL) {
        // printf("work: %lu\tmax: %lu\n", work_ptr, max_ptr);
        struct wfs_log_entry* cur_entry = (struct wfs_log_entry*)work_ptr;
        // printf("chcking log entry %d\n", cur_entry->inode.inode_number);
        if (cur_entry->inode.mode & S_IFDIR &&
            cur_entry->inode.deleted == 0) {  // this is wrong
            struct wfs_dentry* maybe = search_entry_for_name(cur_entry, name);

            if (maybe) {
                // printf("MAYBE %s\n", name);
                name = strtok(NULL, "/");
            }
            if (name == NULL && maybe) {
                return maybe->inode_number;
            }

        } else {
            //?? idk
        }

        work_ptr =
            work_ptr + sizeof(struct wfs_log_entry) + cur_entry->inode.size;
    }

    return -1;
}

struct wfs_inode* path_to_inode(char* path) {
    int inode_num = path_to_inode_number(path);

    // problem with creating new inode (throws error if it doesn't exist yet)
    // printf("inode num: %i\n", inode_num);
    if (inode_num < 0) {
        // printf("could not find error\n");
        // printf("")
        return NULL;
    }

    return find_inode(inode_num);
}

/*
 * DENTRY FUNCTIONS
 */

int calc_num_dentries(struct wfs_log_entry* entry) {
    return entry->inode.size / sizeof(struct wfs_dentry);
}

int attr_from_inode(struct wfs_inode* inode, struct stat* stbuf) {
    // printf("attr from inode\n");
    stbuf->st_dev = 1;
    stbuf->st_ino = inode->inode_number;

    // if (inode->mode & S_IFDIR) {
    //     stbuf->st_mode = inode->mode | S_IFDIR;
    // }
    stbuf->st_mode = inode->mode;

    stbuf->st_nlink = inode->links;
    stbuf->st_uid = inode->uid;
    stbuf->st_gid = inode->gid;
    stbuf->st_rdev = 0;
    stbuf->st_size = inode->size;
    stbuf->st_blksize = 4096;
    stbuf->st_blocks =
        (stbuf->st_size + stbuf->st_blksize - 1) / stbuf->st_blksize;
    stbuf->st_atime = inode->atime;
    stbuf->st_mtime = inode->mtime;
    stbuf->st_ctime = inode->ctime;

    return 0;
}

/*
 * WFS FUNCTIONS
 */

static int wfs_getattr(const char* path, struct stat* stbuf) {
    read_disk();

   // char* path = resolve_path((char*)p);
    printf("getattr-path: %s\n", path);

    //printf("hYEYYYO\n");
    struct wfs_inode* inode = path_to_inode((char*)path);
    printf("after searching\n");
    if (inode == NULL) {
        printf("no inode for: %s\n", path);
        return -ENOENT;
    }

    //printf("FFOUNDDD%d\n", inode->inode_number);
    print_inode(inode);
    stbuf->st_dev = 1;                    // Device ID
    stbuf->st_ino = inode->inode_number;  // Inode number
    stbuf->st_mode = inode->mode;         // Regular file with permissions 0644
    stbuf->st_nlink = inode->links;       // Number of hard links
    stbuf->st_uid = inode->uid;           // User ID of the file owner
    stbuf->st_gid = inode->gid;           // Group ID of the file owner
    stbuf->st_rdev = 0;                   // Device ID (if special file)
    stbuf->st_size = inode->size;         // Size of the file in bytes
    stbuf->st_blksize = 4096;             // Block size for filesystem I/O
    stbuf->st_blocks =
        (stbuf->st_size + stbuf->st_blksize - 1) /
        stbuf->st_blksize;           // Number of 512-byte blocks allocated
    stbuf->st_atime = inode->atime;  // Last access time
    stbuf->st_mtime = inode->mtime;  // Last modification time
    stbuf->st_ctime = inode->ctime;  // Last status change time

    if (strcmp(path, "/") == 0 || inode->inode_number == 0)  // root directory
    {
       // printf("special rule: %s\n", path);
        stbuf->st_mode = S_IFDIR | 00777;
    }
    // if (strcmp(path, ".") == 0) {
    //     stbuf->st_mode = S_IFDIR | 00777;
    // }
    // if (strcmp(path, "..") == 0) {
    //     stbuf->st_mode = S_IFDIR | 00777;
    // }

    // if (stbuf->st_mode & S_IFDIR) {
    //     stbuf->st_mode = stbuf->st_mode | 00777;
    // }
    return 0;  // Return 0 on success
    write_disk();
}
void add_dentry(struct wfs_dentry* new_dentries,
                struct wfs_dentry* old_dentries, int old_num_dentries,
                struct wfs_dentry* toadd) {
    unsigned long work_ptr = (unsigned long)new_dentries;

    for (int i = 0; i < old_num_dentries; i++) {
        struct wfs_dentry* cur_dentry = (struct wfs_dentry*)work_ptr;

        memcpy(cur_dentry, old_dentries, sizeof(struct wfs_dentry));
        old_dentries++;
        work_ptr += sizeof(struct wfs_dentry);
    }

    struct wfs_dentry* last_dentry = (struct wfs_dentry*)work_ptr;

    memcpy(last_dentry, toadd, sizeof(struct wfs_dentry));
}
/**
 * @brief Removes the matching dentry from arg 1 and retursn the remaining as
 * arg2
 *
 */
void remove_and_move_dentry(struct wfs_dentry* entries,
                            struct wfs_dentry* new_entries,
                            int num_original_entries, char* name) {
    unsigned long work_ptr = (unsigned long)entries;
    for (int i = 0, j = 0; i < num_original_entries; i++) {
        struct wfs_dentry* cur_dentry = (struct wfs_dentry*)work_ptr;

        if (strncmp(cur_dentry->name, name, strlen(cur_dentry->name)) != 0) {
            // add
            memcpy(&new_entries[j], cur_dentry, sizeof(struct wfs_dentry));
            j++;
        }
        work_ptr += sizeof(struct wfs_dentry);
    }
}

/**
 * @brief Removes all after last /
 *
 * @param path
 * @return char*
 */
char* getParentPath(char* path) {
    char* parentpath = malloc(strlen(path));

    memcpy(parentpath, path, strlen(path));

    char* last = strrchr(parentpath, '/');
    if (last != NULL) {
        *last = '\0';
    } else {
        *parentpath = '/';
        parentpath++;
        *parentpath = '\0';
    }
    if (strlen(parentpath) == 0) {
        strncpy(parentpath, "/\0", 2);
    }
    return parentpath;
}

char* getFileName(char* path) {
    char* lastSlash = strrchr(path, '/');

    if (lastSlash != NULL) {
        return lastSlash + 1;
    }

    return path;
}

void updateEntries(struct wfs_log_entry* written,
                   struct wfs_log_entry* updated) {
    written->inode.deleted = 1;

    updated->inode.size =
        calc_num_dentries(updated) * sizeof(struct wfs_dentry);
    updated->inode.mtime = time(NULL);
    updated->inode.links = 1;
}

static int wfs_mknod(const char* p, mode_t mode, dev_t rdev) {
    read_disk();
    printf("wfs_mknod\n");
    char* path = resolve_path((char*)p);
    printf("PATH: %s\n", path);  // format of "/[TO MAKE]"

    void* ptr = get_head();
    int nextnum = next_inode_number();
    char* parentPath = getParentPath((char*)path);
    char* name = getFileName((char*)path);

    printf("parent: %s, name: %s\n", parentPath, name);

    int parent_inode_number = path_to_inode_number((char*)parentPath);

    struct wfs_log_entry* parent_entry = get_log_entry(parent_inode_number);

    print_inode(&parent_entry->inode);

    int prev_parent_num_dentries = calc_num_dentries(parent_entry);

    // make new parent
    struct wfs_log_entry* new_parent = ptr;

    clone_inode(&new_parent->inode, &parent_entry->inode);

    parent_entry->inode.deleted = 1;
    new_parent->inode.mtime = time(NULL);
    new_parent->inode.size =
        parent_entry->inode.size + sizeof(struct wfs_dentry);

    struct wfs_dentry* new_parent_dentries =
        (struct wfs_dentry*)new_parent->data;

    struct wfs_dentry* dentry = malloc(sizeof(struct wfs_dentry));

    dentry->inode_number = nextnum;
    printf("num: %i\n", nextnum);
    strncpy(dentry->name, name, strlen(name));
    printf("name: %s\t length: %lu\n", name, strlen(name));
    printf("string:%s\n", dentry->name); 
    add_dentry(new_parent_dentries, (struct wfs_dentry*)&parent_entry->data,
               prev_parent_num_dentries, dentry);

    size_t size_added =
        sizeof(struct wfs_log_entry) +
        (prev_parent_num_dentries + 1) * sizeof(struct wfs_dentry);

    ptr = (void*)((unsigned long)ptr + size_added);

    struct wfs_sb* sb = get_sb();
    sb->head += size_added;
    printf("size added: %lu \n", size_added + sizeof(struct wfs_log_entry));

    struct wfs_log_entry* new_node = (struct wfs_log_entry*)ptr;

    super_default_inode(&new_node->inode, nextnum, mode);
    new_node->inode.size = 0;
    new_node->inode.mode = S_IFREG | 0755;
    sb->head += sizeof(struct wfs_log_entry);

    write_disk();
    printf("wrote disk mknod\n");
    return 0;

    //     read_disk();

    //     char* path = resolve_path((char*)p);
    //     printf("wfs-mknod\n");
    //    // printf("PATH: %s\n", path);  // format of "/[TO MAKE]"

    //     void* ptr = get_head();
    //     int nextnum = next_inode_number();
    //     char* parentPath = getParentPath((char*)path);
    //     char* name = getFileName((char*)path);

    //     printf("parent: %s, name: %s\n", parentPath, name);

    //     int parent_inode_number = path_to_inode_number((char*)parentPath);

    //     struct wfs_log_entry* parent_entry =
    //     get_log_entry(parent_inode_number);

    //     print_inode(&parent_entry->inode);

    //     int prev_parent_num_dentries = calc_num_dentries(parent_entry);

    //     // make new parent
    //     struct wfs_log_entry* new_parent = ptr;

    //     clone_inode(&new_parent->inode, &parent_entry->inode);

    //     parent_entry->inode.deleted = 1;
    //     new_parent->inode.mtime = time(NULL);
    //     new_parent->inode.size =
    //         parent_entry->inode.size + sizeof(struct wfs_dentry);

    //     struct wfs_dentry* new_parent_dentries =
    //         (struct wfs_dentry*)new_parent->data;

    //     struct wfs_dentry* dentry = malloc(sizeof(struct wfs_dentry));

    //     dentry->inode_number = nextnum;
    //     printf("FILENAME HERE NCIK: %s\n", name);
    //     strncpy(dentry->name, name, strlen(name));
    //     add_dentry(new_parent_dentries, (struct
    //     wfs_dentry*)&parent_entry->data,
    //                prev_parent_num_dentries, dentry);

    //     size_t size_added =
    //         sizeof(struct wfs_log_entry) +
    //         (prev_parent_num_dentries + 1) * sizeof(struct wfs_dentry);

    //     ptr = (void*)((unsigned long)ptr + size_added);

    //     struct wfs_sb* sb = get_sb();
    //     sb->head += size_added;
    //     printf("size added: %lu \n", size_added + sizeof(struct
    //     wfs_log_entry));

    //     struct wfs_log_entry* our_dir = (struct wfs_log_entry*)ptr;

    //     super_default_regfile_inode(&our_dir->inode, nextnum);
    //     our_dir->inode.size = 0;
    //     our_dir->inode.mode = mode | 0777;
    //     sb->head += sizeof(struct wfs_log_entry);

    //     write_disk();

    //     printf("mknod:::::end\n");
    //     return 0;

    // read_disk();

    // printf("mknod\n");
    // struct wfs_log_entry* new_entry = malloc(sizeof(struct wfs_log_entry));

    // int number = next_inode_number();
    // super_default_regfile_inode(&new_entry->inode, number);

    // char* parentdir = getParentPath((char*)path);
    // char* filename = getFileName((char*)path);

    // // printf("parentdir:%s, %i\n", parentdir, (int)strlen(parentdir));

    // if (strlen(parentdir) == 0) {
    //     strcpy(parentdir, "/\0");
    // }
    // int written_dir_entry_number = path_to_inode_number((char*)parentdir);

    // if (written_dir_entry_number == -1) {
    //     printf("ERROR: wfs_mknod 1\n");
    //     return -ENOENT;
    // }
    // struct wfs_log_entry* written_dir_entry =
    //     get_log_entry(written_dir_entry_number);

    // if (written_dir_entry == NULL) {
    //     printf("ERROR: wfs_mknod 1\n");
    //     return -ENOENT;
    // }

    // int current_entries_num = calc_num_dentries(written_dir_entry);
    // int updated_entries_num = current_entries_num + 1;
    // struct wfs_log_entry* updated_dir_entry =
    //     malloc(sizeof(struct wfs_log_entry) +
    //            (updated_entries_num) * sizeof(struct wfs_dentry));

    // struct wfs_dentry* dentries =
    //     malloc(updated_entries_num * sizeof(struct wfs_dentry));

    // memcpy(dentries, written_dir_entry->data,
    //        current_entries_num * sizeof(struct wfs_dentry));
    // dentries += current_entries_num;

    // struct wfs_dentry dentry;
    // dentry.inode_number = number;
    // memcpy(&dentry.name, filename, strlen(filename));
    // // dentry.name = filename;

    // memcpy(dentries, &dentry, sizeof(struct wfs_dentry));

    // super_default_dir_inode(&updated_dir_entry->inode,
    //                         updated_dir_entry->inode.inode_number);

    // clone_inode(&updated_dir_entry->inode, &written_dir_entry->inode);
    // updateEntries(written_dir_entry, updated_dir_entry);

    // init_dir_log_entry(updated_dir_entry, dentries, updated_entries_num);
    // printf("wfs_mknod\n");
    // write_disk();
    // return 0;
}

static int wfs_mkdir(const char* p, mode_t mode) {
    read_disk();
    printf("wfs_mkdir\n");
    char* path = resolve_path((char*) p);
    printf("PATH: %s\n", path);  // format of "/[TO MAKE]"

    void* ptr = get_head();
    int nextnum = next_inode_number();
    char* parentPath = getParentPath((char*)path);
    char* name = getFileName((char*)path);

    printf("parent: %s, name: %s\n", parentPath, name);

    int parent_inode_number = path_to_inode_number((char*)parentPath);

    struct wfs_log_entry* parent_entry = get_log_entry(parent_inode_number);

    print_inode(&parent_entry->inode);

    int prev_parent_num_dentries = calc_num_dentries(parent_entry);


    // make new parent
    struct wfs_log_entry* new_parent = ptr;

    clone_inode(&new_parent->inode, &parent_entry->inode);

    parent_entry->inode.deleted = 1;
    new_parent->inode.mtime = time(NULL);
    new_parent->inode.size =
        parent_entry->inode.size + sizeof(struct wfs_dentry);

    struct wfs_dentry* new_parent_dentries =
        (struct wfs_dentry*)new_parent->data;

    struct wfs_dentry* dentry = malloc(sizeof(struct wfs_dentry));

    dentry->inode_number = nextnum;
    printf("d inode num%lu\n", dentry->inode_number);
    strncpy(dentry->name, name, strlen(name));

    printf("string:%s\n", dentry->name);
    add_dentry(new_parent_dentries, (struct wfs_dentry*)&parent_entry->data,
               prev_parent_num_dentries, dentry);

    size_t size_added =
        sizeof(struct wfs_log_entry) +
        (prev_parent_num_dentries + 1) * sizeof(struct wfs_dentry);

    ptr = (void*)((unsigned long)ptr + size_added);

    struct wfs_sb* sb = get_sb();
    sb->head += size_added;
    printf("size added: %lu \n", size_added + sizeof(struct wfs_log_entry));

    struct wfs_log_entry* our_dir = (struct wfs_log_entry*)ptr;
    
    super_default_dir_inode(&our_dir->inode, nextnum);
    our_dir->inode.size =0;
    our_dir->inode.mode = S_IFDIR | 0755;
    sb->head += sizeof(struct wfs_log_entry);

    write_disk();
    return 0;
}

static int wfs_read(const char* p, char* buf, size_t size, off_t offset,
                    struct fuse_file_info* fi) {
    read_disk();
    char* path = resolve_path((char*)p);
    int inode_number = path_to_inode_number((char*)path);

    if (inode_number == -1) {
        return -ENOENT;
    }

    struct wfs_log_entry* entry = get_log_entry(inode_number);

    size_t data_size = entry->inode.size;

    if (offset >= data_size) {
        return 0;
    }

    size_t remaining_size = data_size - offset;

    size_t read_bytes = (size < remaining_size) ? size : remaining_size;

    memcpy(buf, entry->data + offset, size);
    write_disk();  // access times
    return read_bytes;
}

static int wfs_write(const char* p, const char* buf, size_t size,
                     off_t offset, struct fuse_file_info* fi) {
    printf("WFS_WRITE\n");
    
    char* path = resolve_path((char*) p);
    printf("wfs_write: path: %s\n", path);
    read_disk();

    int inode_number = path_to_inode_number((char*)path);
    struct wfs_sb* sb = get_sb();
    struct wfs_log_entry* new_entry = (struct wfs_log_entry*)get_head();

    char* parentPath = getParentPath((char*) path);

    int parent_entry_inode_num = path_to_inode_number((char*) parentPath);

        struct wfs_log_entry* parent_entry = get_log_entry(parent_entry_inode_num);

    int prev_parent_num_dentries = calc_num_dentries(parent_entry);

    char* filename = getFileName((char*) path);
    size_t bytes_written;
    //struct wfs_sb* sb = get_sb();
    if (inode_number < 0) {
        // does not exist, create new

        //create new entry and write to it.

        int new_inode_number = next_inode_number();

        super_default_regfile_inode(&new_entry->inode, new_inode_number);
        size_t size_needed = size + offset;
        printf("size needed: %lu\n", size_needed);
        new_entry->inode.size = size + offset;

        char* data_plus_offset =
            (char*)((unsigned long)&new_entry->data) + offset;

        memcpy(data_plus_offset, buf, size);

        sb->head += sizeof(struct wfs_log_entry) + size_needed;

        bytes_written = size;

        //add directory

        // make new parent
        struct wfs_log_entry* new_parent = get_head();

        clone_inode(&new_parent->inode, &parent_entry->inode);

        parent_entry->inode.deleted = 1;
        new_parent->inode.mtime = time(NULL);
        new_parent->inode.size =
            parent_entry->inode.size + sizeof(struct wfs_dentry);

        struct wfs_dentry* new_parent_dentries =
            (struct wfs_dentry*)new_parent->data;

        struct wfs_dentry* dentry = malloc(sizeof(struct wfs_dentry));
        //int nextnum = next_inode_number();
        dentry->inode_number = new_inode_number;

        printf("FILENAME: %s\n", filename);
        strncpy(dentry->name, filename, strlen(filename));
        add_dentry(new_parent_dentries, (struct wfs_dentry*)&parent_entry->data,
                   prev_parent_num_dentries, dentry);

        size_t size_added =
            sizeof(struct wfs_log_entry) +
            (prev_parent_num_dentries + 1) * sizeof(struct wfs_dentry);

        // ptr = (void*)((unsigned long)ptr + size_added);

        // struct wfs_sb* sb = get_sb();
        sb->head += size_added;


    } else { //file already exists

        struct wfs_log_entry* prev_entry = get_log_entry(inode_number);
        printf("prev entry size: %lu\n", (unsigned long)prev_entry->inode.size);

        clone_inode(&new_entry->inode, &prev_entry->inode);

        size_t total_size = 0;
        if (offset > prev_entry->inode.size) {
            total_size+= offset+ size;
        } else {
            total_size += offset + size;
        }


        prev_entry->inode.deleted = 1;
        new_entry->inode.mtime = time(NULL);
        new_entry->inode.size = total_size;
        new_entry->inode.mode = prev_entry->inode.mode | 0755;
        printf("size needed: %lu\n", (unsigned long)new_entry->inode.size);

        char* data_plus_offset= (char* ) ((unsigned long) &new_entry->data) + offset;

      
        memcpy(data_plus_offset, buf, size);
        printf("data %s\n", data_plus_offset);

        sb->head += sizeof(struct wfs_log_entry) + total_size;

        bytes_written = size;
    }
        //update parent dir

    //     int new_inode = next_inode_number();
    //     super_default_regfile_inode(&new_entry->inode, new_inode);
    //     new_entry->inode.size = size;

    //     char* data_plus_offset = (char*)((unsigned long) &new_entry->data) + offset;

    //     memcpy(data_plus_offset,buf, size );

    //     char* parentPath = getParentPath((char*) path);
    //     char* filename = getFileName((char*) path);

    //     int parent_dir_inode_num = path_to_inode_number(parentPath);

    //     if (parent_dir_inode_num <0) {
    //         printf("this is a problem\n");
    //         return -1;
    //     }



    //     struct wfs_log_entry* parent_dir_entry = get_log_entry(parent_dir_inode_num);

    //     if (parent_dir_entry == NULL) {
    //         printf("this is also a problem\n");
    //         return -1;
    //     }

    //     new_entry = (struct wfs_log_entry*) ((void*) (((unsigned long) new_entry) + (unsigned long) sizeof(struct wfs_log_entry) + size));
    //     struct wfs_log_entry* parent_dir_new_entry= new_entry;
    //     clone_inode(&parent_dir_new_entry->inode, &parent_dir_entry->inode);
        
    //     parent_dir_entry->inode.deleted = 1;

    //     parent_dir_new_entry->inode.size = parent_dir_entry->inode.size + sizeof(struct wfs_dentry);
    //     parent_dir_entry->inode.mtime = time(NULL);
        
    //     int old_num_dentries = calc_num_dentries(parent_dir_entry);

    //     struct wfs_dentry* dentry = malloc(sizeof(struct wfs_dentry));
    //     dentry->inode_number = new_inode;
    //     strncpy(dentry->name, filename, strlen(filename));
    //     add_dentry((struct wfs_dentry*)parent_dir_new_entry->data,
    //                (struct wfs_dentry*)parent_dir_entry->data, old_num_dentries,
    //                dentry);

    //     sb->head += sizeof(struct wfs_log_entry) + sizeof(struct wfs_log_entry) + ((old_num_dentries + 1) * sizeof(struct wfs_dentry));
    //     //updateEntries(parent_dir_entry, parent_dir_new_entry);

    // } else {  // already exists, update
    //     struct wfs_log_entry* old_entry = get_log_entry(inode_number);

    //     if (old_entry->inode.mode & S_IFDIR) {
    //         printf("cannot write to a directory\n");
    //         return -1;  // no eacces?
    //     }

    //     new_entry = (struct wfs_log_entry*) get_head();

    //     int new_inode = next_inode_number();
    //     super_default_regfile_inode(&new_entry->inode, new_inode);
    // }

    // struct wfs_log_entry* newentry = get_head();
    // init_inode(&newentry->inode, entry->inode.inode_number,
    //            entry->inode.deleted, entry->inode.mode, entry->inode.uid,
    //            entry->inode.gid, entry->inode.flags,
    //            entry->inode.size + size + offset, time(NULL), time(NULL),
    //            time(NULL), entry->inode.links);
    // entry->inode.deleted = 1;

    // char* data = entry->data;
    // data += offset;

    // // basically just need to write a check to see if the data got
    // // bigger/changed

    // struct wfs_sb* sb = get_sb();
    // sb->head += sizeof(struct wfs_log_entry) + size + offset;

    write_disk();

    return bytes_written;
}

static int wfs_readdir(const char* p, void* buf, fuse_fill_dir_t filler,
                       off_t offset, struct fuse_file_info* fi) {
    read_disk();
    char* path = resolve_path((char*)p);
    printf("yo path: %s\n", path);
    struct wfs_inode* inode = path_to_inode((char*)path);

    if (inode == NULL) {
        printf("1\n");
        return -ENOENT;
    }
    struct wfs_log_entry* entry = get_log_entry(inode->inode_number);

    if (entry == NULL) {
        printf("2\n");
        return -ENOENT;
    }

    // filler(buf, ".", NULL,0);
    // filler(buf, "..", NULL, 0);

    int num_dentries = calc_num_dentries(entry);

    printf("numb dentries: %i\n", num_dentries);
    unsigned long start_ptr = (unsigned long)entry->data;
    unsigned long work_ptr = start_ptr;

    // int offset=0;
    for (int i = 0; i < num_dentries; i++) {
        work_ptr = start_ptr + (i * sizeof(struct wfs_dentry));
        struct wfs_dentry* dentry = (struct wfs_dentry*)work_ptr;
        printf("dir entry: %i: %s\n", i, dentry->name);
        // struct stat s;
        // get_attr_from_inode(find_inode(dentry->inode_number), &s);

        struct wfs_inode* inode = find_inode(dentry->inode_number);

        if (inode == NULL) {
            if (filler(buf, dentry->name, NULL, 0) != 0) {
                printf("filler problem1\n");
            }
        } else {
            struct stat stbuf;

            attr_from_inode(inode, &stbuf);

            if (filler(buf, dentry->name, &stbuf, 0) != 0) {
                printf("filler problem2\n");
            }
        }
    }

    printf("wfs_readdir\n");
    write_disk();
    return 0;
}
void mark_entry_deleted(struct wfs_log_entry* entry) {
    entry->inode.deleted = 1;
}

static int wfs_unlink(const char* p) {
    read_disk();

    // decrement inode.links
    /**
     * if 0 mark deleted, else nothing shouldn't have to rewrite because its an
     * inode change.
     *
     */
    char* path = resolve_path((char*)p);
    struct wfs_inode* inode = path_to_inode((char*)path);

    if (inode == NULL) {
        printf("ENOENT: wfs_unlink");
        return -ENOENT;
    }

    inode->links--;

    if (inode->links < 1) {
        // delete

        char* parentPath = getParentPath((char*)path);
        if (parentPath == NULL) {
            printf("wfs_unlink: parent null\n");
            return -ENOENT;
        }
        char* filename = getFileName((char*)path);

        if (filename == NULL) {
            printf("wfs_unlink: parent null\n");
            return -ENOENT;
        }

        printf("parent: %s\t file: %s\n", parentPath, filename);
        int parent_dir_inode_number = path_to_inode_number(parentPath);

        struct wfs_log_entry* written = get_log_entry(parent_dir_inode_number);

        int num_dentries = calc_num_dentries(written);

        struct wfs_sb* _sb = get_sb();
        unsigned long sb = (unsigned long)_sb;
        struct wfs_log_entry* updated = (struct wfs_log_entry*)(sb + _sb->head);

        // check disk being full
        remove_and_move_dentry((struct wfs_dentry*)&written->data,
                               (struct wfs_dentry*)&updated->data, num_dentries,
                               filename);

        clone_inode(&updated->inode, &written->inode);
        updated->inode.size = sizeof(struct wfs_dentry) * (num_dentries - 1);
        updated->inode.mtime = time(NULL);
        updateEntries(written, updated);
        //mark_entry_deleted((struct wfs_log_entry*)inode);
        inode->deleted =1;

        updated->inode.deleted = 0;
        size_t total_size = sizeof(struct wfs_log_entry) +
                            sizeof(struct wfs_dentry) * (num_dentries - 1);

        _sb->head += total_size;

        printf("head: %x\n", _sb->head);

        print_inode(&written->inode);
        print_inode(&updated->inode);
    }

    // maybe change parent dir

    printf("wfs_unlink\n");
    write_disk();
    return 0;
}

void* wfs_init(struct fuse_conn_info* conn) {
    printf("wfs_init\n");
    read_disk();
    max_inode = highest_inode_number();
    //$$$check for max inode here
    write_disk();
    return NULL;
}

static struct fuse_operations my_operations = {
    .getattr = wfs_getattr,
    .mknod = wfs_mknod,
    .mkdir = wfs_mkdir,
    .read = wfs_read,
    .write = wfs_write,
    .readdir = wfs_readdir,
    .unlink = wfs_unlink,
    .init = wfs_init,
};

// todo: upgrade this parser -options go to fuse and last argument.  There is
// one skipped.  I'm hard coding it to "disk"
int main(int argc, char* argv[]) {
    int r = 1;  // read index
    int w = 1;  // write index
    //disk_name = argv[argc - 1];
   // printf("disk: %s\n", disk_name);
    //fd = open(disk_name, O_RDWR, 0777);
    
    while (r < argc) {
        if (strstr(argv[r], "mnt") != NULL) {
            printf("mnt match argv:%s\n", argv[r]);

            argv[w] = realpath(argv[r], NULL);
            r++;
            w++;
        } else if (strncmp(argv[r], "-", 1) == 0) {
            argv[w] = argv[r];
            r++;
            w++;
        } else {
            disk_name = argv[r];
            printf("disk: %s\n", disk_name);
            fd = open(disk_name, O_RDWR, 0777);
            r++;
            // argv[w] = argv[r];
            // r++;
            // w++;
        }
        // if (strstr(argv[r], "mnt") != NULL) {
        //     printf("mnt match argv:%s\n", argv[r]);

        //     argv[w] = realpath(argv[r], NULL);
        //     r++;
        //     w++;
        // } else if (strncmp(argv[r], "-", 1) == 0) {
        //     if(argv[r][1] == 'o') {
        //         argv[w++] = argv[r++];
        //         argv[w++] = argv[r++];
        //     } else {
        //         argv[w++] = argv[r++];
        //     }
        // } else {
        //         argv[w++] = argv[r++];
        // }
    }
    argc = w;

    struct stat file_stat;
    if (fstat(fd, &file_stat) == -1) {
        // Handle error
        printf("YOOOOO BAD\n");
        return -1;
    }

    size = file_stat.st_size;


    printf("\ndisk name: %s\ndisk size: %d\n", disk_name, size);
    for (int i = 0; i < argc; i++) {
        printf("Arg %d: %s\n", i, argv[i]);
    }

    return fuse_main(argc, argv, &my_operations, NULL);
}
