#include "types.h"
#include "user.h"
#include <stddef.h>
#include "mmap.h"

int main(void)
{
    void *addr =(void*) mmap((void*)NULL, 1000, PROT_READ | PROT_WRITE,
                      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    printf(1, "ptr: %x\n", addr);

    // void* naddr = addr + 4096;
    // printf(1, "naddr: %x\n", naddr);

    // addr = (void *)mmap(NULL, 1000, PROT_READ | PROT_WRITE,
    //                           MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    // printf(1, "ptr: %x\n", addr);

    // addr = (void *)mmap(NULL, 1000, PROT_READ | PROT_WRITE,
    //                           MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    // printf(1, "ptr: %x\n", addr);

    // void *addr2 = (void *) mmap(naddr, 1000, PROT_READ | PROT_WRITE,
    //                            MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    // printf(1, "ptr2: %x\n", addr2);
    
    //printf(1, "Testing\n%d\n%d\n", mmap(NULL, 2, 3, MAP_GROWSUP, 5, 6), munmap(NULL, -1));
    exit();
}