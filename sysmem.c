#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"

struct header {
  uint magic;          // Magic number to validate headers
  int size;            // Size of this block
  int free;            // Is this block free?
  struct header *next; // Next block in the list
};

#define HEADER_SIZE sizeof(struct header)
#define HEADER_MAGIC 0x12345678  // Magic number to identify valid headers

static struct header *free_list = 0;

// Validates if a header pointer is valid
static int
is_valid_header(struct header *h)
{
  struct proc *p = myproc();
  return h && 
         (uint)h >= PGSIZE && 
         (uint)h < p->sz &&
         h->magic == HEADER_MAGIC &&
         h->size >= HEADER_SIZE &&
         h->size <= p->sz;
}

void*
do_xmalloc(uint nbytes)
{
  if (nbytes == 0) return 0;
  
  struct header *curr = 0, *prev = 0;
  void *block;
  uint total_size = ((nbytes + 7) & ~7) + HEADER_SIZE;
  
  // First-fit search in free list
  if (free_list) {
    curr = free_list;
    while (curr && is_valid_header(curr)) {
      if (curr->free && curr->size >= total_size) {
        curr->free = 0;
        return (void*)((char*)curr + HEADER_SIZE);
      }
      prev = curr;
      curr = curr->next;
    }
    
    // If we found invalid blocks, rebuild the free list
    if (curr && !is_valid_header(curr)) {
      if (prev)
        prev->next = 0;
      else
        free_list = 0;
    }
  }
  
  // Allocate new memory
  struct proc *curproc = myproc();
  uint old_sz = curproc->sz;
  if (growproc(total_size) < 0) 
    return 0;
    
  block = (void*)old_sz;
  struct header *new_block = (struct header*)block;
  new_block->magic = HEADER_MAGIC;
  new_block->size = total_size;
  new_block->free = 0;
  new_block->next = 0;
  
  // Add to free list
  if (!free_list) {
    free_list = new_block;
  } else if (prev && is_valid_header(prev)) {
    prev->next = new_block;
  } else {
    new_block->next = free_list;
    free_list = new_block;
  }
  
  return (void*)((char*)new_block + HEADER_SIZE);
}

void
do_xfree(void* ptr)
{
  if (!ptr) return;
  
  struct header *block = (struct header*)((char*)ptr - HEADER_SIZE);
  if (!is_valid_header(block))
    return;  // Invalid header, ignore this free operation
  
  // Protection against double free
  if (block->free) 
    return;
    
  block->free = 1;
}

void*
do_xcalloc(uint num, uint size)
{
  uint total = num * size;
  char* ptr = (char*)do_xmalloc(total);
  if (!ptr) return 0;
  
  // Zero-initialize the memory
  for (uint i = 0; i < total; i++)
    ptr[i] = 0;
    
  return (void*)ptr;
}

void*
do_xrealloc(void* ptr, uint new_size)
{
  if (!ptr) 
    return do_xmalloc(new_size);
  
  if (new_size == 0) {
    do_xfree(ptr);
    return 0;
  }
  
  struct header *block = (struct header*)((char*)ptr - HEADER_SIZE);
  if (!is_valid_header(block))
    return do_xmalloc(new_size);  // If invalid, just allocate new memory
    
  uint old_size = block->size - HEADER_SIZE;
  
  if (old_size >= new_size)
    return ptr;  // Current block is big enough
  
  // Need a bigger block
  void *new_ptr = do_xmalloc(new_size);
  if (!new_ptr) return 0;
  
  // Copy data to new block
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