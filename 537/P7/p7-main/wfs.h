#include <stddef.h>
#include <stdint.h>

#ifndef MOUNT_WFS_H_
#define MOUNT_WFS_H_

#define MAX_FILE_NAME_LEN 32
#define WFS_MAGIC 0xdeadbeef


struct wfs_sb {
    uint32_t magic;
    uint32_t head;
};

struct wfs_inode {
    unsigned int inode_number;
    unsigned int deleted;       // 1 if deleted, 0 otherwise
    unsigned int mode;          // type. S_IFDIR if the inode represents a directory or S_IFREG if it's for a file
    unsigned int uid;           // user id
    unsigned int gid;           // group id
    unsigned int flags;         // flags
    unsigned int size;          // size in bytes
    unsigned int atime;         // last access time
    unsigned int mtime;         // last modify time
    unsigned int ctime;         // inode change time (the last time any field of inode is modified)
    unsigned int links;         // number of hard links to this file (this can always be set to 1)
};

struct wfs_dentry {
    char name[MAX_FILE_NAME_LEN];
    unsigned long inode_number;
};

struct wfs_log_entry {
    struct wfs_inode inode;
    char data[];
};

char* disk_name;
int fd;
int size;
int max_inode = 0;

int next_inode_number() { return ++max_inode; }
void* start_disk;

void read_disk() {
    start_disk = mmap(NULL, size, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
}

void write_disk() {
    munmap(start_disk, size);
    start_disk = NULL;
}


/*
 * MISC FUNCTIONS
 */

struct wfs_log_entry* get_first_entry() {
    void* ptr = (void*)((unsigned long)start_disk +
                        sizeof(struct wfs_sb));  // advance past superblock

    return ptr;
}

struct wfs_sb* get_sb() {
    void* ptr = (void*)(start_disk);
    return ptr;
}
int highest_inode_number() {
    struct wfs_log_entry* entry = get_first_entry();
    struct wfs_sb* sb = get_sb();
    unsigned long max_ptr = (unsigned long)sb + (unsigned)sb->head;

    void* work_ptr = (void*)entry;

    int highest_inode_number = -1;
    while ((unsigned long)work_ptr < max_ptr) {
        struct wfs_log_entry* cur_entry = work_ptr;
        int cur_number = cur_entry->inode.inode_number;
        if (cur_number > highest_inode_number) {
            highest_inode_number = cur_number;
        }
        work_ptr = (void*)((unsigned long) work_ptr + sizeof(struct wfs_log_entry) + (unsigned long)cur_entry->inode.size);
    }

    return highest_inode_number;
}

/**
 * @brief base function, inits inode to params
 *
 * @param inode
 * @param inode_number
 * @param deleted
 * @param mode
 * @param uid
 * @param gid
 * @param flags
 * @param size
 * @param atime
 * @param mtime
 * @param ctime
 * @param links
 */
void init_inode(struct wfs_inode* inode, unsigned int inode_number,
                unsigned int deleted, unsigned int mode, unsigned int uid,
                unsigned int gid, unsigned int flags, unsigned int size,
                unsigned int atime, unsigned int mtime, unsigned int ctime,
                unsigned int links) {
    inode->inode_number = inode_number;
    inode->deleted = deleted;
    inode->mode = mode;
    inode->uid = uid;
    inode->gid = gid;
    inode->flags = flags;
    inode->size = size;
    inode->atime = atime;
    inode->mtime = mtime;
    inode->ctime = ctime;
    inode->links = links;
}

void super_default_inode(struct wfs_inode* inode, unsigned int inode_number,
                         int type_flag) {
    time_t current_time = time(NULL);

    init_inode(inode, inode_number, 0, type_flag, geteuid(), getegid(), 0, 0,
               current_time, current_time, current_time, 1);
}

size_t size_dir_log_entries(
    int num_dentries) {  // IF WE HAVE PROBLEMS UNSIGNED LONG MIGHT NEED TO BE 4
                         // INSTEAD OF 8!
    return sizeof(struct wfs_dentry) * num_dentries ;//+
          // sizeof(struct wfs_log_entry);
}

void super_default_regfile_inode(struct wfs_inode* inode,
                                 unsigned int inode_number) {
    super_default_inode(inode, inode_number, S_IFREG);
}

void super_default_dir_inode(struct wfs_inode* inode,
                             unsigned int inode_number) {
    super_default_inode(inode, inode_number, S_IFDIR);

    inode->size = size_dir_log_entries(0);
}

void clone_inode(struct wfs_inode* dest, struct wfs_inode* src) {
    memcpy(dest, src, sizeof(struct wfs_inode));
}

void init_dir_log_entry(struct wfs_log_entry* entry,
                        struct wfs_dentry* dentries, int num_dentries) {
    super_default_dir_inode(&entry->inode, next_inode_number());

    struct wfs_dentry* cur = (void*)entry->data;

    for (int i = 0; i < num_dentries; i++) {
        memcpy(cur, &dentries[i], sizeof(struct wfs_dentry));
        cur++;
    }
}

#endif
