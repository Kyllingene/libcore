#ifndef _CORE_MALLOCH
#define _CORE_MALLOCH

#include "../types/types.hpp"

//! Allocate `size` bytes on the heap.
//! 
//! Must be freed later using `free`.
void* malloc(size_t size);

//! Allocate `size` bytes on the heap and zero them.
void* calloc(size_t nelem, size_t elsize);

//! Reuse `ptr` if possible, else allocate `size` bytes on the heap.
void* realloc(void* ptr, size_t size);

//! Free memory that has been allocated.
void free(void* ptr);

#endif