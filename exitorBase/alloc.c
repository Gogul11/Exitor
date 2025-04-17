#include "../types.h"
#include "../user.h"

struct header {
  int size;              
  int free;              
  struct header* next;
};
#define HEADER_SIZE sizeof(struct header)
static struct header* free_list = 0;

void* xmalloc(uint nbytes) {
  struct header *curr, *prev = 0;
  void* block;

  int total_size = ((nbytes + 7) & ~7) + HEADER_SIZE;  
  if (!free_list) {
    block = sbrk(total_size);
    if ((int)block == -1) return 0;

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

  block = sbrk(total_size);
  if ((int)block == -1) return 0;

  struct header* new_block = (struct header*)block;
  new_block->size = total_size;
  new_block->free = 0;
  new_block->next = 0;

  prev->next = new_block;
  return (void*)((char*)new_block + HEADER_SIZE);
}

void xfree(void* ptr) {
  if (!ptr) return;
  struct header* block = (struct header*)((char*)ptr - HEADER_SIZE);
  block->free = 1;
}

void* xcalloc(uint num, uint size) {
  int total = num * size;
  char* ptr = (char*)xmalloc(total);
  if (!ptr) return 0;

  for (int i = 0; i < total; i++)
    ptr[i] = 0;

  return (void*)ptr;
}


void* xrealloc(void* ptr, uint new_size) {
  if (!ptr) {
    
    return xmalloc(new_size);
  }

  if (new_size == 0) {
   
    xfree(ptr);
    return 0;
  }

  struct header* block = (struct header*)((char*)ptr - HEADER_SIZE);
  uint old_size = block->size - HEADER_SIZE;
  if (old_size >= new_size) {
    return ptr;
  }

  
  void* new_ptr = xmalloc(new_size);
  if (!new_ptr) return 0;

 
  memmove(new_ptr, ptr, old_size);
  

  xfree(ptr);

  return new_ptr;
}
