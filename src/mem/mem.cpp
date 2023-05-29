#include "mem.hpp"

void* memset(void* dest, int data, size_t size) {
    for (size_t i = 0; i < size; i++)
        ((char*)dest)[i] = data;

    return dest;
}

void* memcpy(void* source, const void* dest, size_t size) {
    for (size_t i = 0; i < size; i++)
        ((char*)dest)[i] = ((char*)source)[i];

    return source;
}
