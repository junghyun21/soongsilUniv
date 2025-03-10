#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "spinlock.h"

#define TIME_SLICE 10000000 // time_slice 정의
#define NULL ((void*)0)

int weight = 1; // weight(가중치) 변수 선언

// ptable: 구조체를 딱 한 번만 선언해서 사용함 -> 전역변수 느낌
struct {
  struct spinlock lock;
  struct proc proc[NPROC]; // NPPROC: 프로세스의 최대 개수
  long long min_priority; // 프로세스의 독점을 막기 위해 우선순위 값 중 가장 작은 값 저장
} ptable;

static struct proc *initproc;

int nextpid = 1;
extern void forkret(void);
extern void trapret(void);

static void wakeup1(void *chan);

// 과제 3-1: ssu_scheduler
// 기존의 scheduler를 수정하여서 구현
// main.c에서 호출
// 스케줄러는 처음 호출이 된 후, 종료되지 않고 무한반복되며 사용됨
void scheduler(void)
{
  struct proc *p;
  struct proc *running_p;
  struct cpu *c = mycpu();
  c->proc = 0;

  // ssu_scheduler 또한 처음 호출된 후, 종료되지 않고 무한반복 되며 사용됨
  // 프로세스 실행이 시작될 때 호출
  for(;;){
    sti(); // 해당 프로세서에서 모든 인터럽트에 대해 enable

    acquire(&ptable.lock);

    running_p = NULL;

    // 실행시킬 process를 찾기 위해 process table 탐색하며 loop 진행 -> 우선순위의 값이 가장 낮은 프로세스 찾기
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    {
      if(p->state != RUNNABLE)
      {
        continue;
      }

      if(running_p == NULL || p->priority < running_p->priority)
      {
        running_p = p;
      }

    }

// 디버깅 모드로 컴파일 할 때만 실행
#ifdef DEBUG
  if (running_p)
    cprintf("PID: %d, NAME: %s, WEIGHT: %d, PRIORITY: %d\n", running_p->pid, running_p->name, running_p->weight, running_p->priority);
#endif

    if(running_p == NULL)
    {
      release(&ptable.lock);
      continue;
    }

    c->proc = running_p;
    switchuvm(running_p);
    running_p->state = RUNNING;

    swtch(&(c->scheduler), running_p->context);
    switchkvm();

    update_priority(running_p); // 방금 실행했던 프로세스의 우선순위 업데이트
    update_min_priority(); // 우선순위 값 중 가장 작은 값 업데이트

    // Process is done running for now
    // It should have changed its p->state before coming back.
    c->proc = 0;

    release(&ptable.lock);
  }
}

// 스케줄링 함수가 호출될 때마다 방금 선택받았던 프로세스의 우선순위는 새로 업데이트 됨
void update_priority(struct proc *proc)
{
  proc->priority = proc->priority + (TIME_SLICE / proc->weight);
}


void update_min_priority()
{
  struct proc *min = NULL; 
  struct proc *p;

  // 가장 작은 priority 값 저장 (우선순위가 가장 높은 값)
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
  {
    if(p->state == RUNNABLE)
    {
      if(min == NULL || p->priority < min->priority)
      {
        min = p;
      }
    }
  }

  if(min != NULL)
  {
    ptable.min_priority = min->priority;
  }
}

// 프로세스 생성 또는 wake up시, 우선순위를 0부터 부여하게 되면 해당 프로세스가 독점 실행될 수 있음
// 따라서 프로세스의 우선순위 값 중 가장 작은 값을 부여함
void assign_min_priority(struct proc *proc)
{
  proc->priority = ptable.min_priority;
}

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
// 새로 생성된 프로세스가 저장될 공간을 탐색하고 할당하기 위한 함수
static struct proc* allocproc(void)
{
  struct proc *p;
  char *sp;

  acquire(&ptable.lock);

  // process table에 신규 프로세스를 할당할 공간이 있는지 확인
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    if(p->state == UNUSED)
      goto found;

  release(&ptable.lock);
  return 0;

found:
  // 우선 사용하지 않는 공간이 있으면 우선 해당 공간을 EMBRYO 상태로 정의
  p->state = EMBRYO;
  // nextpid: proc.c 내부에 전역변수로 선언되어 있음 (int nextpid = 1;)
  // nextpid를 현재의 pid로 지정하고 1 증가
  p->pid = nextpid++; 
  p->weight = weight++; // 가중치 부여 및 1 증가
  // weight++;
  assign_min_priority(p); // 우선순위 부여

  release(&ptable.lock);

  // Allocate kernel stack.
  // 신규 proc 구조체에 커널스택 메모리 할당
  // 실패하면 proc 구조를 다시 UNUSED 상태(사용되지 않은 공간)로 변경
  if((p->kstack = kalloc()) == 0){
    p->state = UNUSED;
    return 0;
  }
  // stack 포인터 위치 지정
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

  return p;
}

//PAGEBREAK: 32
// Set up first user process.
void
userinit(void)
{
  struct proc *p;
  extern char _binary_initcode_start[], _binary_initcode_size[];

  ptable.min_priority = 3; // 최소 우선순위는 3부터 시작

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
  // 새로 생성된 프로세스가 저장될 수 있는 곳을 찾기 위해 process table을 탐색
  // 테이블 내에 할당할 공간이 없거나, 커널스택 메모리를 할당하지 못하면 0 리턴
  // np는 process table 내에 프로세스가 저장될 곳, 초기화된 프로세스 구조체
  if((np = allocproc()) == 0){
    return -1;
  }

  // Copy process state from proc.
  // 프로세스 테이블 내, 프로세스를 저장하는 곳에 새로 생성된 프로세스의 정보 저장
  if((np->pgdir = copyuvm(curproc->pgdir, curproc->sz)) == 0){
    kfree(np->kstack);
    np->kstack = 0;
    np->state = UNUSED;
    return -1;
  }
  np->sz = curproc->sz;
  np->parent = curproc; // 부모 프로세스를 현재 프로세스로 설정(현재 프로세스로부터 생성되었기 때문)
  *np->tf = *curproc->tf; // 부모가 가지고 있던 trapframe를 새로 생성한 자식 프로세스에게 복사

  // Clear %eax so that fork returns 0 in the child.
  // 자식 프로세스는 forkret 후 trapret으로 돌아갈 때 리턴값으로 eax 값을 사용
  // 그래서 자식 프로세스의 리턴값이 0
  np->tf->eax = 0;

  // 부모의 열려진 파일 목록 및 현재 디렉토리 관련 정보를 자식에게 복사
  for(i = 0; i < NOFILE; i++)
    if(curproc->ofile[i])
      np->ofile[i] = filedup(curproc->ofile[i]);
  np->cwd = idup(curproc->cwd);

  // 부모 프로세스 이름을 자식 프로세스에게 복사
  safestrcpy(np->name, curproc->name, sizeof(curproc->name));

  pid = np->pid; // 자식의 pid를 부모에게 전달

  acquire(&ptable.lock);

  np->state = RUNNABLE; // 자식 프로세스의 상태를 EMBRYO에서 RUNNABLE로 변경

  release(&ptable.lock);

  return pid; // 부모는 자식 프로세스의 pid를 리턴
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

// PAGEBREAK: 42
// Per-CPU process scheduler.
// Each CPU calls scheduler() after setting itself up.
// Scheduler never returns.  It loops, doing:
//  - choose a process to run
//  - swtch to start running that process
//  - eventually that process transfers control
//      via swtch back to the scheduler.
// void
// scheduler(void)
// {
//   struct proc *p;
//   struct cpu *c = mycpu();
//   c->proc = 0;

//   cprintf("start scheduler\n");
  
//   for(;;){
//     // Enable interrupts on this processor.
//     sti();

//     // Loop over process table looking for process to run.
//     acquire(&ptable.lock);
//     for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
//       if(p->state != RUNNABLE)
//         continue;

//       // Switch to chosen process.  It is the process's job
//       // to release ptable.lock and then reacquire it
//       // before jumping back to us.
//       c->proc = p;
//       switchuvm(p);
//       p->state = RUNNING;

//       swtch(&(c->scheduler), p->context);
//       switchkvm();

//       // Process is done running for now.
//       // It should have changed its p->state before coming back.
//       c->proc = 0;
//     }
//     release(&ptable.lock);

//   }
// }

// Enter scheduler.  Must hold only ptable.lock
// and have changed proc->state. Saves and restores
// intena because intena is a property of this
// kernel thread, not this CPU. It should
// be proc->intena and proc->ncli, but that would
// break in the few places where a lock is held but
// there's no process.
// 기존의 정보 저장
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
// chan은 구조체 proc의 멤버 변수
static void wakeup1(void *chan)
{
  struct proc *p;

  // wake up할 process를 찾기 위해 process table 탐색하며 loop 진행
  // wake up: process의 상태를 SLEEPING에서 RUNNABLE으로 전환시키는 것
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    if(p->state == SLEEPING && p->chan == chan)
    {
      p->state = RUNNABLE;

      // process를 wake up 했을 때, 우선순위 값 중 가장 작은 값을 부여해야함
      assign_min_priority(p);
    }
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

// sys_weightset() 시스템 콜을 위한 커널 함수
void weightset(int weight)
{
  acquire(&ptable.lock);
  myproc()->weight = weight;
  release(&ptable.lock);
}