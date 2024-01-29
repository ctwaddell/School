#include <linux/stat.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#include "errno.h"
#include "fcntl.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "wfs.h"

size_t size_sb() {
    return sizeof(struct wfs_sb);
}

size_t size_log_entry() {
    return sizeof(struct wfs_log_entry);
}

/*
mkfs.wfs.c
This C program initializes a file to an empty filesystem. The program receives a
path to the disk image file as an argument, i.e., mkfs.wfs disk_path initializes
the existing file disk_path to an empty filesystem (Fig. a).
*/

void mkfs(int fd) {
    size_t total_size = size_sb() + size_log_entry();

    char* ptr = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    
    struct wfs_sb* superblock = (void*)ptr;
    superblock->magic = WFS_MAGIC;
    superblock->head += size_sb();
    ptr += size_sb();

    struct wfs_log_entry* root_entry = (void*)ptr;
    super_default_dir_inode(&root_entry->inode, 0);
    root_entry->inode.size = 0;
    superblock->head += sizeof(struct wfs_log_entry);
    root_entry->inode.mode =  S_IFDIR | 0777;

    munmap(ptr, total_size);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        return -ENOENT;
    }

    int fd = open(argv[1], O_RDWR, 0777);

    if (fd < 0) {
        return -ENOENT;
    }

    mkfs(fd);

    return 0;
}
