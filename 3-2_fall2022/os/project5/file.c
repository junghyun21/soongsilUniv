//
// File descriptors
//

#include "types.h"
#include "defs.h"
#include "param.h"
#include "fs.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "file.h"

struct devsw devsw[NDEV];
struct {
  struct spinlock lock;
  struct file file[NFILE];
} ftable;

void
fileinit(void)
{
  initlock(&ftable.lock, "ftable");
}

// Allocate a file structure.
struct file*
filealloc(void)
{
  struct file *f;

  acquire(&ftable.lock);
  // 빈 곳이 있는지 파일 테이블 탐색
  for(f = ftable.file; f < ftable.file + NFILE; f++){
    if(f->ref == 0){
      f->ref = 1;
      release(&ftable.lock);
      return f;
    }
  }
  release(&ftable.lock);
  return 0;
}

// Increment ref count for file f.
struct file*
filedup(struct file *f)
{
  acquire(&ftable.lock);
  if(f->ref < 1)
    panic("filedup");
  f->ref++;
  release(&ftable.lock);
  return f;
}

// Close file f.  (Decrement ref count, close when reaches 0.)
void
fileclose(struct file *f)
{
  struct file ff;

  acquire(&ftable.lock);
  if(f->ref < 1)
    panic("fileclose");
  if(--f->ref > 0){
    release(&ftable.lock);
    return;
  }
  ff = *f;
  f->ref = 0;
  f->type = FD_NONE;
  release(&ftable.lock);

  if(ff.type == FD_PIPE)
    pipeclose(ff.pipe, ff.writable);
  else if(ff.type == FD_INODE){
    begin_op();
    iput(ff.ip); // 더 이상 참조가 없으면 inode 할당 해제 
    end_op();
  }
}

// Get metadata about file f.
int
filestat(struct file *f, struct stat *st)
{
  if(f->type == FD_INODE){
    ilock(f->ip);
    stati(f->ip, st);
    iunlock(f->ip);
    return 0;
  }
  return -1;
}

// Read from file f.
int
fileread(struct file *f, char *addr, int n)
{
  int r;

  // 파일에 읽기 권한이 없는 경우 -> 에라
  if(f->readable == 0)
    return -1;
  // 파일 타입이 FD_PIPE인 경우
  if(f->type == FD_PIPE)
    return piperead(f->pipe, addr, n);
  // 파일 타입이 FD_INODE인 경우 -> CS 기반 파일을 위한 read 메커니즘 추가해야함 (아마?)
  if(f->type == FD_INODE){
    ilock(f->ip);
    if((r = readi(f->ip, addr, f->off, n)) > 0)
      f->off += r;
    iunlock(f->ip);
    return r;
  }
  panic("fileread");
}

//PAGEBREAK!
// Write to file f.
// addr가 가리키는 값들을 n크기만큼 f에 기술
int
filewrite(struct file *f, char *addr, int n)
{
  int r;

  // 파일이 쓰기 권한이 없는 경우 -> 에러
  if(f->writable == 0)
    return -1;
  // 파일 타입이 FD_PIPE인 경우
  if(f->type == FD_PIPE)
    return pipewrite(f->pipe, addr, n);
  // 파일 타입이 FD_INODE인 경우 -> CS 기반 파일을 위한 데이터 할당 메커니즘 추가해야함
  if(f->type == FD_INODE){
    // write a few blocks at a time to avoid exceeding
    // the maximum log transaction size, including
    // i-node, indirect block, allocation blocks,
    // and 2 blocks of slop for non-aligned writes.
    // this really belongs lower down, since writei()
    // might be writing a device like the console.
    int max = ((MAXOPBLOCKS-1-1-2) / 2) * 512; // 하나의 데이터 블록에 저장할 수 있는 파일의 최대 크기
    int i = 0; // i: addr이 가리키는 값들 중 저장을 시작할 곳
    while(i < n){
      int n1 = n - i; // n1: 저장할 크기
      if(n1 > max)
        n1 = max; // 하나의 데이터 블록에 저장할 수 있는 파일의 최대 크기를 초과한 경우 -> 최대값까지 저장 후, 다음 데이터 블록에 저장

      begin_op();
      ilock(f->ip); // writei() 사용 전에 ip->lock 잠궈야함
      // writei(): fs.c 내부에 존재 -> i-node에 데이터 작성
      // 리턴값: n1 -> 쓴 데이터 크기
      if ((r = writei(f->ip, addr + i, f->off, n1)) > 0)
        f->off += r; // 데이터 쓴 만큼 오프셋 증가
      iunlock(f->ip);
      end_op();

      if(r < 0)
        break;
      if(r != n1)
        panic("short filewrite");
      i += r;
    }
    return i == n ? n : -1;
  }
  panic("filewrite");
}

