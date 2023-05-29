#ifndef _CORE_CRALLOCH
#define _CORE_CRALLOCH

#include "../types/types.hpp"

//! Allocate `size` bytes on the heap.
//! 
//! Must be freed later using `free`.
void* cralloc(size_t size);

//! Allocate `size` bytes on the heap and zero them.
void* zalloc(size_t size);

//! Resize `ptr` if possible, else allocate `size` bytes on the heap and copy the data over.
void* crealloc(void* ptr, size_t size);

//! Free memory that has been allocated.
void cree(void* ptr);

extern "C" void *_brk(size_t new_break); // defined in brk.s, just the brk syscall
void *sbrk(ssize_t offset);

#endif