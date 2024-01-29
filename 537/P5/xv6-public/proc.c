#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "spinlock.h"
#include <stddef.h>


struct {
  struct spinlock lock;
  struct proc proc[NPROC];
} ptable;

static struct proc *initproc;

int nextpid = 1;
extern void forkret(void);
extern void trapret(void);

static void wakeup1(void *chan);

int getMappingWhereFaultOccurs(struct proc* p, void* addr) {


  for (int i =0; i < 32; i++) {
    if (p->memmap[i].isBeingUsed == 0) {
      continue;
    }

    if (addr >=p->memmap[i].addr && addr < p->memmap[i].addr + p->memmap[i].length) {
      return i;
    }
  }

  return -1;
}


void printMemMaps(struct proc *p) {
    // struct proc* p = myproc();

    for (int i = 0; i < 32; i++) {
        if (p->memmap[i].isBeingUsed == 0) {
            continue;
        } else {
            cprintf(
                "addr: %x\tfd: %d\tflags: %d\tisbeingused: %d\tlength: "
                "%d\toffset: "
                "%d\tpagecount: %d\tprot: %d\n",
                p->memmap[i].addr, p->memmap[i].fd, p->memmap[i].flags,
                p->memmap[i].isBeingUsed, p->memmap[i].length,
                p->memmap[i].offset, p->memmap[i].pagecount, p->memmap[i].prot);
        }
    }
}

int compare_mmap_by_addr(void *a, void *b) {
    const struct mmap *mmap_a = (const struct mmap *)a;
    const struct mmap *mmap_b = (const struct mmap *)b;

    if (mmap_a->isBeingUsed == 0 && mmap_b->isBeingUsed == 0) {
        return 0;
    }
    if (mmap_a->isBeingUsed == 1 && mmap_b->isBeingUsed == 0) {
        return 1;
    }
    if (mmap_a->isBeingUsed == 0 && mmap_b->isBeingUsed == 1) {
        return -1;
    }
    if (mmap_a->addr < mmap_b->addr) return -1;
    if (mmap_a->addr > mmap_b->addr) return 1;
    return 0;
}

void bubble_sort(struct mmap *arr, int size) {
    int swapped;
    do {
        swapped = 0;
        for (int i = 1; i < size; i++) {
            if (compare_mmap_by_addr(&arr[i - 1], &arr[i]) < 0) {
                // Swap the elements if they are out of order
                struct mmap temp = arr[i - 1];
                arr[i - 1] = arr[i];
                arr[i] = temp;
                swapped = 1;
            }
        }
    } while (swapped);
}

void sortMappings(struct proc *p) { bubble_sort(p->memmap, 32); }
/**
 * @brief Adds a mapping to process
 * always sort processes with sortMappings after modifying a proc mmap, this
 * makes it easier to keep order.
 *
 * @param mmap
 * @return int 1 on sucess, 0 otherwise
 */
int addMapping(struct proc *p, struct mmap *mmap) {
    // struct proc* p = myproc();
    for (int i = 0; i < 32; i++) {
        if (p->memmap[i].isBeingUsed == 1) {
            continue;
        }

        p->memmap[i] = *mmap;
        sortMappings(p);

        return 1;
    }

    return 0;
}
/**
 * @brief Does the logic for checking a bit
 *
 * @param flags all flags int
 * @param flag specific flag you want to check int
 * @return int 1 if true, 0 otherwise
 */
int _hasFlag(int flags, int flag) { return (flags & flag) == flag; }

/**
 * @brief Checks if a mmap has a specific flag
 *
 * @param mmap
 * @param flag
 * @return int 1 if true, 0 otherwise
 */
int hasFlag(struct mmap *mmap, int flag) { return _hasFlag(mmap->flags, flag); }

/**
 * @brief Checks if a mmap has a specific prot
 *
 * @param mmap
 * @param prot
 * @return int 1 if true, 0 otherwise
 */
int hasProt(struct mmap *mmap, int prot) { return _hasFlag(mmap->prot, prot); }

int _hasProt(int prots, int prot) { return (prots & prot) == prot; }

void
pinit(void)
{
  initlock(&ptable.lock, "ptable");
}

// Must be called with interrupts disabled
int
cpuid() {
  return mycpu()-cpus;
}

// Must be called with interrupts disabled to avoid the caller being
// rescheduled between reading lapicid and running through the loop.
struct cpu*
mycpu(void)
{
  int apicid, i;
  
  if(readeflags()&FL_IF)
    panic("mycpu called with interrupts enabled\n");
  
  apicid = lapicid();
  // APIC IDs are not guaranteed to be contiguous. Maybe we should have
  // a reverse map, or reserve a register to store &cpus[i].
  for (i = 0; i < ncpu; ++i) {
    if (cpus[i].apicid == apicid)
      return &cpus[i];
  }
  panic("unknown apicid\n");
}

// Disable interrupts so that we are not rescheduled
// while reading proc from the cpu structure
struct proc*
myproc(void) {
  struct cpu *c;
  struct proc *p;
  pushcli();
  c = mycpu();
  p = c->proc;
  popcli();
  return p;
}

//PAGEBREAK: 32
// Look in the process table for an UNUSED proc.
// If found, change state to EMBRYO and initialize
// state required to run in the kernel.
// Otherwise return 0.
static struct proc*
allocproc(void)
{
  struct proc *p;
  char *sp;

  acquire(&ptable.lock);

  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    if(p->state == UNUSED)
      goto found;

  release(&ptable.lock);
  return 0;

found:
  p->state = EMBRYO;
  p->pid = nextpid++;

  release(&ptable.lock);

  // Allocate kernel stack.
  if((p->kstack = kalloc()) == 0){
    p->state = UNUSED;
    return 0;
  }
  sp = p->kstack + KSTACKSIZE;

  // Leave room for trap frame.
  sp -= sizeof *p->tf;
  p->tf = (struct trapframe*)sp;

  // Set up new context to start executing at forkret,
  // which returns to trapret.
  sp -= 4;
  *(uint*)sp = (uint)trapret;

  sp -= sizeof *p->context;
  p->context = (struct context*)sp;
  memset(p->context, 0, sizeof *p->context);
  p->context->eip = (uint)forkret;


  p->pagetable = setupkvm(); //setup page table
  p->memmap = (void*)kalloc(); //init memmap
  memset(p->memmap, 0, 32 * sizeof(struct mmap));
  //cprintf("sizeof memmap: %d\n", sizeof(struct mmap));
   
  if (p->pagetable==0) {
    kfree(p->kstack);
    p->kstack= 0;
    p->state = UNUSED;
    return 0;
  } 


  return p;
}

//PAGEBREAK: 32
// Set up first user process.
void
userinit(void)
{
  struct proc *p;
  extern char _binary_initcode_start[], _binary_initcode_size[];

  p = allocproc();
  
  initproc = p;
  if((p->pgdir = setupkvm()) == 0)
    panic("userinit: out of memory?");
  inituvm(p->pgdir, _binary_initcode_start, (int)_binary_initcode_size);
  p->sz = PGSIZE;
  memset(p->tf, 0, sizeof(*p->tf));
  p->tf->cs = (SEG_UCODE << 3) | DPL_USER;
  p->tf->ds = (SEG_UDATA << 3) | DPL_USER;
  p->tf->es = p->tf->ds;
  p->tf->ss = p->tf->ds;
  p->tf->eflags = FL_IF;
  p->tf->esp = PGSIZE;
  p->tf->eip = 0;  // beginning of initcode.S

  safestrcpy(p->name, "initcode", sizeof(p->name));
  p->cwd = namei("/");

  // this assignment to p->state lets other cores
  // run this process. the acquire forces the above
  // writes to be visible, and the lock is also needed
  // because the assignment might not be atomic.
  acquire(&ptable.lock);

  p->state = RUNNABLE;

  release(&ptable.lock);
}

// Grow current process's memory by n bytes.
// Return 0 on success, -1 on failure.
int
growproc(int n)
{
  uint sz;
  struct proc *curproc = myproc();

  sz = curproc->sz;
  if(n > 0){
    if((sz = allocuvm(curproc->pgdir, sz, sz + n)) == 0)
      return -1;
  } else if(n < 0){
    if((sz = deallocuvm(curproc->pgdir, sz, sz + n)) == 0)
      return -1;
  }
  curproc->sz = sz;
  switchuvm(curproc);
  return 0;
}

int getPhysicalPage(struct proc *p, int tempaddr, pte_t **pte) {
    *pte = walkpgdir(p->pgdir, (char *)tempaddr, 0);
    if (!*pte) {
        return 0;
    }
    int pa = PTE_ADDR(**pte);
    return pa;
}

void cpy_memmap(struct mmap* parent, struct mmap* child) {
    child->addr = parent->addr;
    child->length = parent->length;
    child->flags = parent->flags;
    child->prot = parent->prot;
    child->fd = parent->fd;
    child->offset = parent->offset;
    
}
int copy_maps(struct proc *parent, struct proc *child) {
    pte_t *pte;
    for (int i = 0; i < 32; i++) {
      if (parent->memmap[i].isBeingUsed == 0) {
        continue;
      }

      int va = (int)parent->memmap[i].addr;
      int prot = parent->memmap[i].prot;
      int isShared = hasFlag(&parent->memmap[i], MAP_SHARED);
      int length = parent->memmap[i].length;
      for (int start = va; start < va + length; start += PGSIZE) {

        

        if (isShared) { // shared

          char* parentmem= (char*) P2V(getPhysicalPage(parent, va, &pte));
          if (mappages(child->pgdir, (void*) va, PGSIZE, V2P(parentmem), prot | PTE_U | PTE_W) <0) {
            //cprintf("error\n");
            return -1;
          }

        } else {  // private
            char *childmem = kalloc();
            if (childmem == 0) {
                // Handle memory allocation failure.
                return -1;
            }
            memmove(childmem, (void *)va,
                    PGSIZE);  // Copy data from parent to child.
            if (mappages(child->pgdir, (void *)va, PGSIZE, V2P(childmem),
                         prot | PTE_U| PTE_W) < 0) {
                // Handle mappages error.
                return -1;
            }
        }

        addMapping(child, &parent->memmap[i]);
        //cpy_memmap(&child->memmap[i], &parent->memmap[i]);
        //sortMappings(child);

        // printMemMaps(parent);

        //  printMemMaps(child);
      }
    }

    return 0;
}

// Create a new process copying p as the parent.
// Sets up stack to return as if from system call.
// Caller must set state of returned proc to RUNNABLE.
int
fork(void)
{
  int i, pid;
  struct proc *np;
  struct proc *curproc = myproc();

  // Allocate process.
  if((np = allocproc()) == 0){
    return -1;
  }

  // Copy process state from proc.
  if((np->pgdir = copyuvm(curproc->pgdir, curproc->sz)) == 0){
    kfree(np->kstack);
    np->kstack = 0;
    np->state = UNUSED;
    return -1;
  }


  if (copy_maps(curproc, np) <0) {
    kfree(np->kstack);
    np->kstack = 0;
    np->state = UNUSED;
    return -1;
  }
  np->sz = curproc->sz;
  np->parent = curproc;
  *np->tf = *curproc->tf;

  // Clear %eax so that fork returns 0 in the child.
  np->tf->eax = 0;

  for(i = 0; i < NOFILE; i++)
    if(curproc->ofile[i])
      np->ofile[i] = filedup(curproc->ofile[i]);
  np->cwd = idup(curproc->cwd);

  safestrcpy(np->name, curproc->name, sizeof(curproc->name));

  pid = np->pid;

  acquire(&ptable.lock);

  np->state = RUNNABLE;

  release(&ptable.lock);

  return pid;
}

// Exit the current process.  Does not return.
// An exited process remains in the zombie state
// until its parent calls wait() to find out it exited.
void
exit(void)
{
  struct proc *curproc = myproc();
  struct proc *p;
  int fd;

  if(curproc == initproc)
    panic("init exiting");

  // Close all open files.
  for(fd = 0; fd < NOFILE; fd++){
    if(curproc->ofile[fd]){
      fileclose(curproc->ofile[fd]);
      curproc->ofile[fd] = 0;
    }
  }

  for (int i = 0; i < 32; i++) {
    if (curproc->memmap[i].isBeingUsed == 0) {
      continue;
    }
    proc_memunmap(curproc, curproc->memmap[i].addr, curproc->memmap[i].length);
  }

  begin_op();
  iput(curproc->cwd);
  end_op();
  curproc->cwd = 0;

  acquire(&ptable.lock);

  // Parent might be sleeping in wait().
  wakeup1(curproc->parent);

  // Pass abandoned children to init.
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->parent == curproc){
      p->parent = initproc;
      if(p->state == ZOMBIE)
        wakeup1(initproc);
    }
  }

  // Jump into the scheduler, never to return.
  curproc->state = ZOMBIE;
  sched();
  panic("zombie exit");
}

// Wait for a child process to exit and return its pid.
// Return -1 if this process has no children.
int
wait(void)
{
  struct proc *p;
  int havekids, pid;
  struct proc *curproc = myproc();
  
  acquire(&ptable.lock);
  for(;;){
    // Scan through table looking for exited children.
    havekids = 0;
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
      if(p->parent != curproc)
        continue;
      havekids = 1;
      if(p->state == ZOMBIE){
        // Found one.
        pid = p->pid;
        kfree(p->kstack);
        p->kstack = 0;
        freevm(p->pgdir);
        p->pid = 0;
        p->parent = 0;
        p->name[0] = 0;
        p->killed = 0;
        p->state = UNUSED;
        release(&ptable.lock);
        return pid;
      }
    }

    // No point waiting if we don't have any children.
    if(!havekids || curproc->killed){
      release(&ptable.lock);
      return -1;
    }

    // Wait for children to exit.  (See wakeup1 call in proc_exit.)
    sleep(curproc, &ptable.lock);  //DOC: wait-sleep
  }
}

//PAGEBREAK: 42
// Per-CPU process scheduler.
// Each CPU calls scheduler() after setting itself up.
// Scheduler never returns.  It loops, doing:
//  - choose a process to run
//  - swtch to start running that process
//  - eventually that process transfers control
//      via swtch back to the scheduler.
void
scheduler(void)
{
  struct proc *p;
  struct cpu *c = mycpu();
  c->proc = 0;
  
  for(;;){
    // Enable interrupts on this processor.
    sti();

    // Loop over process table looking for process to run.
    acquire(&ptable.lock);
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
      if(p->state != RUNNABLE)
        continue;

      // Switch to chosen process.  It is the process's job
      // to release ptable.lock and then reacquire it
      // before jumping back to us.
      c->proc = p;
      switchuvm(p);
      p->state = RUNNING;

      swtch(&(c->scheduler), p->context);
      switchkvm();

      // Process is done running for now.
      // It should have changed its p->state before coming back.
      c->proc = 0;
    }
    release(&ptable.lock);

  }
}

// Enter scheduler.  Must hold only ptable.lock
// and have changed proc->state. Saves and restores
// intena because intena is a property of this
// kernel thread, not this CPU. It should
// be proc->intena and proc->ncli, but that would
// break in the few places where a lock is held but
// there's no process.
void
sched(void)
{
  int intena;
  struct proc *p = myproc();

  if(!holding(&ptable.lock))
    panic("sched ptable.lock");
  if(mycpu()->ncli != 1)
    panic("sched locks");
  if(p->state == RUNNING)
    panic("sched running");
  if(readeflags()&FL_IF)
    panic("sched interruptible");
  intena = mycpu()->intena;
  swtch(&p->context, mycpu()->scheduler);
  mycpu()->intena = intena;
}

// Give up the CPU for one scheduling round.
void
yield(void)
{
  acquire(&ptable.lock);  //DOC: yieldlock
  myproc()->state = RUNNABLE;
  sched();
  release(&ptable.lock);
}

// A fork child's very first scheduling by scheduler()
// will swtch here.  "Return" to user space.
void
forkret(void)
{
  static int first = 1;
  // Still holding ptable.lock from scheduler.
  release(&ptable.lock);

  if (first) {
    // Some initialization functions must be run in the context
    // of a regular process (e.g., they call sleep), and thus cannot
    // be run from main().
    first = 0;
    iinit(ROOTDEV);
    initlog(ROOTDEV);
  }

  // Return to "caller", actually trapret (see allocproc).
}

// Atomically release lock and sleep on chan.
// Reacquires lock when awakened.
void
sleep(void *chan, struct spinlock *lk)
{
  struct proc *p = myproc();
  
  if(p == 0)
    panic("sleep");

  if(lk == 0)
    panic("sleep without lk");

  // Must acquire ptable.lock in order to
  // change p->state and then call sched.
  // Once we hold ptable.lock, we can be
  // guaranteed that we won't miss any wakeup
  // (wakeup runs with ptable.lock locked),
  // so it's okay to release lk.
  if(lk != &ptable.lock){  //DOC: sleeplock0
    acquire(&ptable.lock);  //DOC: sleeplock1
    release(lk);
  }
  // Go to sleep.
  p->chan = chan;
  p->state = SLEEPING;

  sched();

  // Tidy up.
  p->chan = 0;

  // Reacquire original lock.
  if(lk != &ptable.lock){  //DOC: sleeplock2
    release(&ptable.lock);
    acquire(lk);
  }
}

//PAGEBREAK!
// Wake up all processes sleeping on chan.
// The ptable lock must be held.
static void
wakeup1(void *chan)
{
  struct proc *p;

  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    if(p->state == SLEEPING && p->chan == chan)
      p->state = RUNNABLE;
}

// Wake up all processes sleeping on chan.
void
wakeup(void *chan)
{
  acquire(&ptable.lock);
  wakeup1(chan);
  release(&ptable.lock);
}

// Kill the process with the given pid.
// Process won't exit until it returns
// to user space (see trap in trap.c).
int
kill(int pid)
{
  struct proc *p;

  acquire(&ptable.lock);
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->pid == pid){
      p->killed = 1;
      // Wake process from sleep if necessary.
      if(p->state == SLEEPING)
        p->state = RUNNABLE;
      release(&ptable.lock);
      return 0;
    }
  }
  release(&ptable.lock);
  return -1;
}

//PAGEBREAK: 36
// Print a process listing to console.  For debugging.
// Runs when user types ^P on console.
// No lock to avoid wedging a stuck machine further.
void
procdump(void)
{
  static char *states[] = {
  [UNUSED]    "unused",
  [EMBRYO]    "embryo",
  [SLEEPING]  "sleep ",
  [RUNNABLE]  "runble",
  [RUNNING]   "run   ",
  [ZOMBIE]    "zombie"
  };
  int i;
  struct proc *p;
  char *state;
  uint pc[10];

  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->state == UNUSED)
      continue;
    if(p->state >= 0 && p->state < NELEM(states) && states[p->state])
      state = states[p->state];
    else
      state = "???";
    cprintf("%d %s %s", p->pid, state, p->name);
    if(p->state == SLEEPING){
      getcallerpcs((uint*)p->context->ebp+2, pc);
      for(i=0; i<10 && pc[i] != 0; i++)
        cprintf(" %p", pc[i]);
    }
    cprintf("\n");
  }
}


void* MAPERROR = (void*)-1;

int num_mappings() {
  int count = 0;
  struct proc *p = myproc();
   for (int i = 0; i < 32; i++) {
      if (p->memmap->isBeingUsed == 1) {
          count++;
      }
  }
  return count;
}


int isPageAligned(void * ptr) {
  if ((long)ptr % PGSIZE == 0) {
    return 1;
  } else {
    return 0;
  }
}

/**
 * @brief Handle guard page size insize of function, num_pages is user pages usable pages, not with guard.
 * 
 * @param num_pages 
 * @return void* 
 */
void* findFirstMemorySlot(struct proc* p, int num_pages) {
  sortMappings(p);
    
  int count = num_mappings(); // this might be kinda suspect but trust!

  if (count == 0) {
    // no mappings, return base mapping
    return (void*)0x60000000;
  }

  for (int i = 0; i < count; i++) { //checking to see if our space can fit between two others.
    if (p->memmap[i].isBeingUsed != 1) {
      return MAPERROR;
    }

    if (i == count - 1) {  // last one
      continue;
    }

    //first ending to next start
    void* first_ending = p->memmap[i].addr+ p->memmap[i].length + PGSIZE; //end + guard
        
    return p->memmap[i].addr;
  }
  //probably return next available cause no fits
  return MAPERROR;
}


void* memmap(void* addr, int length, int prot, int flags, int fd, int offset)
{
  struct proc* p = myproc();

  struct file* f = NULL;
  if(!_hasFlag(flags, MAP_ANONYMOUS)) { //not anonymous = file backed
    if((f = myproc()->ofile[fd]) == 0) {
      return MAPERROR;
    }
    setFileOffset(f, 0);
  }

  if (addr == NULL) {
    if(_hasFlag(flags, MAP_FIXED)) return MAPERROR; //piazza @1128
    //we have to establish the pointer, otherwise we return what they put in.
  } else {
    if ((long)addr % PGSIZE != 0) {
      return MAPERROR;
      // Invalid Address, is not page alligned
    }
    if ((long)addr < 0x60000000 ||(long) addr >= 0x80000000) {
      return MAPERROR;
    }
  }

  int num_pages = PGROUNDUP(length) / PGSIZE;

  num_pages++;
  //check if already occupied / any conflicts

  for(int i = 0; i < 32; i++) {
    // Check for an overlap between the new mapping and the existing
    // memory region
    if (p->memmap[i].isBeingUsed == 0) {
      continue;
    }
    if (addr + length > p->memmap[i].addr && addr < p->memmap[i].addr + (num_pages * PGSIZE)) {
      // Overlap found; the address range is occupied
      return MAPERROR;  // Return an error code or handle the error as needed
    } 
  }

  //find addr if needed 
  if (addr == NULL) {
    addr = findFirstMemorySlot(p, num_pages);
  }

  //Allocate pages, update page tables, insert guard pages
  for(void* start = addr; start < addr + length; start += PGSIZE) {
    void *page = kalloc();
    memset(page, 0, PGSIZE);
    if (!_hasFlag(flags, MAP_ANONYMOUS)) {
      // Read data from the file into the allocated page

      int bytesToRead = addr + length - start > PGSIZE ? PGSIZE : addr + length - start;
      int bytesRead = fileread(f, page, bytesToRead);

      if (bytesRead < 0) {
        kfree(page);
        return MAPERROR;
      }

      if (mappages(p->pgdir, start, PGSIZE, V2P(page), prot | PTE_P | PTE_W | PTE_U)) {
        kfree(page);
        return MAPERROR;
      }
    } else { //anon
       if (mappages(p->pgdir, (void *)start, PGSIZE, V2P(page), prot | PTE_P | PTE_U | PTE_W) < 0) {
        kfree(page);
        return MAPERROR;
      }
    }  
  }

  pte_t *pte = walkpgdir(p->pgdir, addr+ length + PGSIZE, 1);
  if (pte) {
      *pte &= ~PTE_P;  // Clear the "PTE_P" flag to make the page not present
  }

  struct mmap memmap;
  memmap.addr = addr;
  memmap.length = length;
  memmap.prot = prot;
  memmap.flags = flags;
  memmap.fd = fd;
  memmap.offset = offset;
  memmap.isBeingUsed = 1;

  return (void*) memmap.addr;
}


int findRegionIndex(struct proc* p, void* addr) {
  for (int i = 0; i < 32; i++) {
    if (p->memmap[i].isBeingUsed == 0) {
      continue;
    } 

    if (addr == p->memmap[i].addr ) {
      return i;
    }
  }
  return -1;
}


int removeMapping(struct proc* p, void* addr) {
  for(int i = 0; i < 32; i++) {
    if (p->memmap[i].isBeingUsed == 0) {
      continue;
    }

    if (p->memmap[i].addr == addr) {
      if (!(p->memmap->flags & MAP_ANONYMOUS)) {
        if (_hasFlag(p->memmap[i].flags, MAP_SHARED) && _hasProt(p->memmap[i].prot, PROT_WRITE)) {
          struct file *f = p->ofile[p->memmap[i].fd];

          if (f != 0) {
            setFileOffset(f, 0);
            int num_pages = PGROUNDUP(p->memmap[i].length) / PGSIZE;
            for (void* a = p->memmap[i].addr; a < addr + (PGSIZE * num_pages); a += PGSIZE) {
              filewrite(f, a, PGSIZE);  // MIGHT HAVE TO EXPAND WITH GROWS_UP
            }
          } else {
        }
      }
    }
    p->memmap[i].isBeingUsed = 0;
    sortMappings(p);
    return 1;
    }
  }

  sortMappings(p);
  return -1;
}


int proc_memunmap(struct proc* p, void * addr, int length) {
    // Determine the number of pages in the memory region
    int regionIndex = findRegionIndex(p, addr);
    int num_pages = PGROUNDUP(length) / PGSIZE;

    for (int i = 0; i < num_pages; i++) {
      void *page_va = p->memmap[regionIndex].addr + i * PGSIZE;
    }

    void *guard_va = p->memmap[regionIndex].addr + (num_pages * PGSIZE);

    if (removeMapping(p, addr) != 1) {
        //cprintf("problem removing mapping\n");
    }

    return 0;
}


int memunmap(void* addr, int length)
{
  //addr checks
  if(addr == NULL) return -1;

  //length checks
  if(length <= 0) return -1;

  return proc_memunmap(myproc(), addr, length);
}