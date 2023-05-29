#include "mem.hpp"

void* memset(void* dest, int data, size_t size) {
    for (size_t i = 0; i < size; i++)
        *(int*)((size_t)dest + i) = data;

    return dest;
}

void* memcpy(void* source, const void* dest, size_t size) {
    for (size_t i = 0; i < size; i++)
        *(int*)((size_t)source + i) = *(int*)((size_t)dest + i);

    return source;
}
