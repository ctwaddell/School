/* Define mmap flags */
#define MAP_PRIVATE 0x0001
#define MAP_SHARED 0x0002
#define MAP_ANONYMOUS 0x0004
#define MAP_ANON MAP_ANONYMOUS
#define MAP_FIXED 0x0008
#define MAP_GROWSUP 0x0010
// We can imagine the above hexes being OR'd together to create combinations of flags, i.e.,
// MAP_PRIVATE | MAP_ANONYMOUS == 0x0005 (Note there is no #define for 0x0005).


/* Protections on memory mapping */
#define PROT_READ 0x1
#define PROT_WRITE 0x2

struct mmap {
  void* addr;
  int length;
  int prot;
  int flags;
  int fd;
  int offset;
  int pagecount;
  int isBeingUsed; // 1 if being used, 0 otherwise..  we will need to memset mmap when we initialize the array of mmap
};

//int MAX_MEMMAP = 32;
