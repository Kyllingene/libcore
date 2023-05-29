#include "cralloc.hpp"
#include "../mem/mem.hpp"
extern "C" void *_brk(size_t new_break); // defined in brk.s, just the brk syscall

void *start_block = nullptr;

struct block_meta {
  size_t size;
  struct block_meta *next;
  bool free;
};

void *get_break() { return _brk(0); }

struct block_meta *get_block_ptr(void *ptr) {
  return (struct block_meta *)ptr - 1;
}

void *sbrk(ssize_t offset) {
  if (!offset)
    return get_break();
  else
    return _brk((size_t)get_break() + offset);
}

struct block_meta *find_free_block(struct block_meta **last, size_t size) {
  struct block_meta *current = (struct block_meta*)start_block;
  while (current && !(current->free && current->size >= size)) {
    *last = current;
    current = current->next;
  }
  return current;
}

struct block_meta *request_space(struct block_meta *last, size_t size) {
  struct block_meta *block;
  block = (struct block_meta*)sbrk(0);
  void *request = sbrk(size + sizeof(struct block_meta));
  if (request == (void *)-1)
    return nullptr; // sbrk failed.

  if (last) // NULL on first request.
    last->next = block;
  block->size = size;
  block->next = nullptr;
  block->free = false;
  return block;
}

void *cralloc(size_t size) {
  struct block_meta *block;
  // TODO: align size?

  if (size <= 0)
    return nullptr;

  if (!start_block) { // First call.
    block = request_space(nullptr, size);
    if (!block)
      return nullptr;
    start_block = block;
  } else {
    struct block_meta *last = (struct block_meta*)start_block;
    block = find_free_block(&last, size);
    if (!block) { // Failed to find free block.
      block = request_space(last, size);
      if (!block)
        return nullptr;
    } else { // Found free block
      // TODO: consider splitting block here.
      block->free = false;
    }
  }

  return (block + 1);
}

void *zalloc(size_t size) {
  void *ptr = cralloc(size);
  if (!ptr)
    return nullptr;

  memset(ptr, 0, size);
  return ptr;
}

void *crealloc(void *ptr, size_t size) {
  if (!ptr) {
    // NULL ptr. realloc should act like malloc.
    return cralloc(size);
  }

  struct block_meta *block_ptr = get_block_ptr(ptr);
  if (block_ptr->size >= size)
    // We have enough space. Could free some once we implement split.
    return ptr;

  // Need to really realloc. Malloc new space and free old space.
  // Then copy old data to new space.
  void *new_ptr = cralloc(size);
  if (!new_ptr)
    return nullptr; // TODO: set errno on failure.
  memcpy(ptr, new_ptr, block_ptr->size);
  cree(ptr);
  return new_ptr;
}

//! Free memory allocated by `malloc` or `calloc`.
void cree(void *ptr) {
  if (!ptr)
    return;

  // TODO: consider merging blocks once splitting blocks is implemented.
  struct block_meta *block_ptr = get_block_ptr(ptr);
  if (block_ptr->free)
    return;

  block_ptr->free = true;
}

void operator delete  ( void* ptr, size_t sz ) noexcept {
  cree(ptr);
}

void operator delete  ( void* ptr ) noexcept {
  cree(ptr);
}
