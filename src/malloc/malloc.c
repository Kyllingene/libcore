#include "malloc.h"
#include "../mem/mem.h"
extern void *_brk(size_t new_break); // defined in brk.s, just the brk syscall

void *start_block = NULL;

struct block_meta {
  size_t size;
  struct block_meta *next;
  int free;
};

void *get_break() { return _brk(0); }

struct block_meta *get_block_ptr(void *ptr) {
  return (struct block_meta *)ptr - 1;
}

void *sbrk(size_st offset) {
  if (!offset)
    return get_break();
  else
    return _brk((size_t)get_break() + offset);
}

struct block_meta *find_free_block(struct block_meta **last, size_t size) {
  struct block_meta *current = start_block;
  while (current && !(current->free && current->size >= size)) {
    *last = current;
    current = current->next;
  }
  return current;
}

struct block_meta *request_space(struct block_meta *last, size_t size) {
  struct block_meta *block;
  block = sbrk(0);
  void *request = sbrk(size + sizeof(struct block_meta));
  if (request == (void *)-1)
    return NULL; // sbrk failed.

  if (last) // NULL on first request.
    last->next = block;
  block->size = size;
  block->next = NULL;
  block->free = 0;
  return block;
}

void *malloc(size_t size) {
  struct block_meta *block;
  // TODO: align size?

  if (size <= 0)
    return NULL;

  if (!start_block) { // First call.
    block = request_space(NULL, size);
    if (!block)
      return NULL;
    start_block = block;
  } else {
    struct block_meta *last = start_block;
    block = find_free_block(&last, size);
    if (!block) { // Failed to find free block.
      block = request_space(last, size);
      if (!block)
        return NULL;
    } else { // Found free block
      // TODO: consider splitting block here.
      block->free = 0;
    }
  }

  return (block + 1);
}

void *calloc(size_t nelem, size_t elsize) {
  size_t size = nelem * elsize; // TODO: check for overflow.
  void *ptr = malloc(size);
  if (!ptr)
    return NULL;

  memset(ptr, 0, size);
  return ptr;
}

void *realloc(void *ptr, size_t size) {
  if (!ptr) {
    // NULL ptr. realloc should act like malloc.
    return malloc(size);
  }

  struct block_meta *block_ptr = get_block_ptr(ptr);
  if (block_ptr->size >= size)
    // We have enough space. Could free some once we implement split.
    return ptr;

  // Need to really realloc. Malloc new space and free old space.
  // Then copy old data to new space.
  void *new_ptr;
  new_ptr = malloc(size);
  if (!new_ptr)
    return NULL; // TODO: set errno on failure.
  memcpy(new_ptr, ptr, block_ptr->size);
  free(ptr);
  return new_ptr;
}

//! Free memory allocated by `malloc` or `calloc`.
void free(void *ptr) {
  if (!ptr)
    return;

  // TODO: consider merging blocks once splitting blocks is implemented.
  struct block_meta *block_ptr = get_block_ptr(ptr);
  if (block_ptr->free)
    return;

  block_ptr->free = 1;
}
