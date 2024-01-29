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
    printf("\n---MAIN TESTS\n---");
    Mem_Dump();
    printf("\nTOO BIG ALLOC\n");
    Mem_Alloc(1600);
    Mem_Dump();
    printf("\nFREE AA\n");
    Mem_Free(p[3]);
    Mem_Dump();
    printf("\nFREE AA2\n");
    Mem_Free(p[5]);
    Mem_Dump();
    printf("\nFREE FF\n");
    Mem_Free(p[4]);
    Mem_Dump();
    printf("\nREEALLOC SIZE 5\n");
    Mem_Alloc(5);
    Mem_Dump();
    printf("\nALLOC ALMOST TOO BIG\n");
    void* swagger = Mem_Alloc(984);
    Mem_Dump();
    printf("\nFREE THAT ALMOST BIG ONE\n");
    Mem_Free(swagger);
    Mem_Dump();
    printf("\nALLOC TOO BIG!!!\n");
    void* swag = Mem_Alloc(985);
    Mem_Dump();
    printf("\nTEST FA\n");
    Mem_Free(p[10]);
    Mem_Dump();
    printf("\npt2\n");
    Mem_Free(p[11]);
    Mem_Dump();
    printf("\nTEST AF\n");
    Mem_Free(p[14]);
    Mem_Dump();
    Mem_Free(p[13]);
    Mem_Dump();
    Free_Memory_Allocator();
    return 0;
}
