#include "mem.h"
#include <stdio.h>

int main() {
    Initialize_Memory_Allocator(1600);
    Mem_Dump();
   
    char *p[25];
    for (int i = 1; i < 24; i++)
      {
      Mem_Dump();
      if((p[i] = Mem_Alloc(i)) == NULL) {
            printf("Allocation failed\n");
            exit(0);
        }
      }
    Mem_Dump();

    Mem_Free(p[3]);
    Mem_Dump();
    void* randomPointer;
    int swag = Mem_Free(randomPointer);
    Mem_Dump();
    printf("\n\n%d\n\n", swag);
    Free_Memory_Allocator();
    return 0;
}
