#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

void*
sys_mmap(void)
{

      begin_op();
    void* addr;

     if (argint(0, (void*)&addr) < 0) return (void*)-1;

    int length;
    if (argint(1, &length) < 0) return (void*)-1;
    //cprintf("length: %d\n", length);
    int prot;
    if (argint(2, &prot) < 0) return (void*)-1;
    //cprintf("prot: %d\n", prot);
    int flags;
    if (argint(3, &flags) < 0) return (void*)-1;
    //cprintf("flags: %d\n", flags);
    int fd;
    if (argint(4, &fd) < 0) return (void*)-1;
    //cprintf("fd: %d\n", fd);
    int offset;
    if (argint(5, &offset) < 0) return (void*)-1;
    //cprintf("offset: %d\n", offset);
    end_op();
    return memmap(addr, length, prot, flags, fd, offset);
}

int
sys_munmap(void)
{
  void* addr;
  if(argint(0, (void*)&addr) < 0) return -1;

  int length;
  if(argint(1, &length) < 0) return -1;

  return memunmap(addr, length);
}

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
