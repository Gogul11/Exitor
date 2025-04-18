#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"

struct header {
  int size;            
  int free;            
  struct header *next; 
};

#define HEADER_SIZE sizeof(struct header)
static struct header *free_list = 0;


void*
do_xmalloc(uint nbytes) {
  struct header *curr, *prev = 0;
  void *block;
  int total_size = ((nbytes + 7) & ~7) + HEADER_SIZE; 
  
  if (!free_list) {
    
    struct proc *curproc = myproc();
    uint old_sz = curproc->sz;
    
    if(growproc(total_size) < 0) return 0;
    block = (void*)old_sz;
    
    free_list = (struct header*)block;
    free_list->size = total_size;
    free_list->free = 0;
    free_list->next = 0;
    return (void*)((char*)block + HEADER_SIZE);
  }
  
  curr = free_list;
  while (curr) {
    if (curr->free && curr->size >= total_size) {
      curr->free = 0;
      return (void*)((char*)curr + HEADER_SIZE);
    }
    prev = curr;
    curr = curr->next;
  }
  
  struct proc *curproc = myproc();
  uint old_sz = curproc->sz;
  
  if(growproc(total_size) < 0) return 0;
  block = (void*)old_sz;
  
  struct header *new_block = (struct header*)block;
  new_block->size = total_size;
  new_block->free = 0;
  new_block->next = 0;
  prev->next = new_block;
  return (void*)((char*)new_block + HEADER_SIZE);
}

void
do_xfree(void* ptr) {
  if (!ptr) return;
  struct header *block = (struct header*)((char*)ptr - HEADER_SIZE);
  block->free = 1;
}

void*
do_xcalloc(uint num, uint size) {
  int total = num * size;
  char *ptr = (char*)do_xmalloc(total);
  if (!ptr) return 0;
  for (int i = 0; i < total; i++)
    ptr[i] = 0;
  return (void*)ptr;
}

void*
do_xrealloc(void* ptr, uint new_size) {
  if (!ptr) {
    return do_xmalloc(new_size);
  }
  if (new_size == 0) {
    do_xfree(ptr);
    return 0;
  }
  struct header *block = (struct header*)((char*)ptr - HEADER_SIZE);
  uint old_size = block->size - HEADER_SIZE;
  if (old_size >= new_size) {
    return ptr;
  }
  void *new_ptr = do_xmalloc(new_size);
  if (!new_ptr) return 0;
  memmove(new_ptr, ptr, old_size);
  do_xfree(ptr);
  return new_ptr;
}


int
sys_xmalloc(void)
{
  int nbytes;
  void *result;
  
  if(argint(0, &nbytes) < 0)
    return -1;
  
  result = do_xmalloc(nbytes);
  return (int)result;
}

int
sys_xfree(void)
{
  int ptr;
  if(argint(0, &ptr) < 0)
    return -1;
    
  do_xfree((void*)ptr);
  return 0;
}

int
sys_xrealloc(void)
{
  int ptr, new_size;
  void *result;
  
  if(argint(0, &ptr) < 0 || argint(1, &new_size) < 0)
    return -1;
    
  result = do_xrealloc((void*)ptr, new_size);
  return (int)result;
}

int
sys_xcalloc(void)
{
  int num, size;
  void *result;
  
  if(argint(0, &num) < 0 || argint(1, &size) < 0)
    return -1;
    
  result = do_xcalloc(num, size);
  return (int)result;
}