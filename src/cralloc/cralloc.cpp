#include "cralloc.hpp"
#include "../mem/mem.hpp"
extern "C" void *_brk(size_t new_break); // defined in brk.s, just the brk syscall

void *start_block = nullptr;
void *end_block = nullptr;

struct block_meta {
  size_t size;
  // struct block_meta *next;
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

struct block_meta *find_free_block(size_t size) {
  struct block_meta *current = (struct block_meta*)start_block;
  while ((current != end_block) && !(current->free && current->size >= size)) {
    // *last = current;
    current = (block_meta*)((size_t)current + current->size + sizeof(block_meta));
  }
  return current;
}

struct block_meta *request_space(size_t size) {
  struct block_meta *block;
  block = (struct block_meta*)get_break();
  void *request = sbrk(size + sizeof(struct block_meta));
  if (request == (void *)-1)
    // return nullptr; // sbrk failed.
    throw "cralloc: sbrk failed";

  end_block = block;
  block->size = size;
  block->free = false;
  return block;
}

void *cralloc(size_t size) {
  struct block_meta *block;
  // TODO: align size?

  if (size == 0)
    return nullptr;

  if (!start_block) { // First call.
    block = request_space(size);
    if (!block)
      throw "cralloc: initial request_space failed";
    start_block = block;
  } else {
    // struct block_meta *last = (struct block_meta*)start_block;
    block = find_free_block(size);
    if (!block || block == end_block) { // Failed to find free block.
      block = request_space(size);
      if (!block)
        throw "cralloc: request_space failed";
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
    throw "zalloc: cralloc failed";

  memset(ptr, 0, size);
  return ptr;
}

void *crealloc(void *ptr, size_t size) {
  if (!ptr) {
    // nullptr. realloc should act like malloc.
    void *new_ptr = cralloc(size);
    if (!new_ptr)
      throw "crealloc: cralloc failed";

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
    throw "crealloc: cralloc failed";
  memcpy(ptr, new_ptr, block_ptr->size);
  cree(ptr);
  return new_ptr;
}

void cree(void *ptr) {
  if (!ptr)
    return;

  // TODO: consider merging blocks once splitting blocks is implemented.
  struct block_meta *block_ptr = get_block_ptr(ptr);
  if (block_ptr->free)
    return;

  block_ptr->free = true;
}

void return_space() {
  struct block_meta *current = (struct block_meta*)start_block;
  struct block_meta *last_used = 0;
  while (current != end_block) {
    // *last = current;
    if (!current->free)
      last_used = current;

    current = (block_meta*)((size_t)current + current->size + sizeof(block_meta));
  }

  if (current != end_block) {
    if (!last_used)
      _brk((size_t)start_block);
    else
      _brk((size_t)last_used + last_used->size + sizeof(block_meta));
  }
}

void operator delete  ( void* ptr, size_t sz ) noexcept {
  cree(ptr);
}

void operator delete  ( void* ptr ) noexcept {
  cree(ptr);
}
