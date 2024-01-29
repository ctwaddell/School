#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "x86.h"
#include "traps.h"
#include "spinlock.h"




int handlePageFault() {
  //cprintf("page fault\n");

  void* fault_va = (void*) rcr2();

  void* last_page = (void*)PGROUNDDOWN((int)fault_va) - PGSIZE;
  struct proc* p = myproc();
  int index = getMappingWhereFaultOccurs(p, last_page);

  if (index == -1) {
      cprintf("Segmentation Fault\n");
      p->killed = 1;
      //exit();
      //kill(p->pid);
      return -1;
  }
  
  if (p->memmap[index].flags & MAP_GROWSUP) {
    //check if it can grow up
    void* new_guard = last_page + (2* PGSIZE);

    int test = getMappingWhereFaultOccurs(p, new_guard);

    if (test ==-1) {
       // printMemMaps(p);
        void* mem = kalloc();
  
        mappages(p->pgdir, last_page + PGSIZE, PGSIZE, V2P(mem),
                     p->memmap[index].prot | PTE_P | PTE_W | PTE_U);
        
        p->memmap[index].length = p->memmap->length + PGSIZE;

        pte_t* pte = walkpgdir(p->pgdir, new_guard, 1);
        if (pte) {
            *pte &=~PTE_P;  // Clear the "PTE_P" flag to make the page not present
        }
       
    } else {
        cprintf("Segmentation Fault\n");
        p->killed = 1;
        //exit();
        return -1;
    }

  } else {
      cprintf("Segmentation Fault\n");
      p->killed = 1;
      //exit();
      return -1;
  }
   //cprintf("%x\n", fault_va);




  
    // int fault_va = rcr2();  // Retrieve the faulting virtual address
    // int fault_page = PGROUNDDOWN(fault_va);

    // pte_t *pte = walkpgdir(myproc()->pgdir, (void *)fault_page, 1);

    // if (pte == 0 || !(*pte & PTE_P)) {
    //     // Page is missing, allocate a free page, load data, and update the page
    //     // table
    //     char *page = kalloc();
    //     if (page == 0) {
    //         // Handle memory allocation failure
    //         return -1;
    //     }

    //     // Load data into 'page' (e.g., from a file) and set necessary flags
    //     // ...

    //     *pte = V2P(page) | PTE_P | PTE_U | PTE_W;

    //     // Optionally, invalidate TLB entries if needed
    //     // lcr3(V2P(myproc()->pgdir));

    //     return 0;
    // } 
    // return -1;
    return 0; 
}

// Interrupt descriptor table (shared by all CPUs).
struct gatedesc idt[256];
extern uint vectors[];  // in vectors.S: array of 256 entry pointers
struct spinlock tickslock;
uint ticks;

void
tvinit(void)
{
  int i;

  for(i = 0; i < 256; i++)
    SETGATE(idt[i], 0, SEG_KCODE<<3, vectors[i], 0);
  SETGATE(idt[T_SYSCALL], 1, SEG_KCODE<<3, vectors[T_SYSCALL], DPL_USER);

  initlock(&tickslock, "time");
}

void
idtinit(void)
{
  lidt(idt, sizeof(idt));
}

//PAGEBREAK: 41
void
trap(struct trapframe *tf)
{
  if(tf->trapno == T_SYSCALL){
    if(myproc()->killed)
      exit();
    myproc()->tf = tf;
    syscall();
    if(myproc()->killed)
      exit();
    return;
  }

  switch(tf->trapno){
  case T_IRQ0 + IRQ_TIMER:
    if(cpuid() == 0){
      acquire(&tickslock);
      ticks++;
      wakeup(&ticks);
      release(&tickslock);
    }
    lapiceoi();
    break;
  case T_IRQ0 + IRQ_IDE:
    ideintr();
    lapiceoi();
    break;
  case T_IRQ0 + IRQ_IDE+1:
    // Bochs generates spurious IDE1 interrupts.
    break;
  case T_IRQ0 + IRQ_KBD:
    kbdintr();
    lapiceoi();
    break;
  case T_IRQ0 + IRQ_COM1:
    uartintr();
    lapiceoi();
    break;
  case T_IRQ0 + 7:
  case T_IRQ0 + IRQ_SPURIOUS:
    cprintf("cpu%d: spurious interrupt at %x:%x\n",
            cpuid(), tf->cs, tf->eip);
    lapiceoi();
    break;


  case T_PGFLT:
    handlePageFault();
    break;
  //PAGEBREAK: 13
  default:
    if(myproc() == 0 || (tf->cs&3) == 0){
      // In kernel, it must be our mistake.
      cprintf("unexpected trap %d from cpu %d eip %x (cr2=0x%x)\n",
              tf->trapno, cpuid(), tf->eip, rcr2());
      panic("trap");
    }
    // In user space, assume process misbehaved.
    cprintf("pid %d %s: trap %d err %d on cpu %d "
            "eip 0x%x addr 0x%x--kill proc\n",
            myproc()->pid, myproc()->name, tf->trapno,
            tf->err, cpuid(), tf->eip, rcr2());
    myproc()->killed = 1;
  }

  // Force process exit if it has been killed and is in user space.
  // (If it is still executing in the kernel, let it keep running
  // until it gets to the regular system call return.)
  if(myproc() && myproc()->killed && (tf->cs&3) == DPL_USER)
    exit();

  // Force process to give up CPU on clock tick.
  // If interrupts were on while locks held, would need to check nlock.
  if(myproc() && myproc()->state == RUNNING &&
     tf->trapno == T_IRQ0+IRQ_TIMER)
    yield();

  // Check if the process has been killed since we yielded
  if(myproc() && myproc()->killed && (tf->cs&3) == DPL_USER)
    exit();
}
