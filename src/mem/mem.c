#include "mem.h"

void* memset(void* dest, int data, size_t size) {
    for (size_t i = 0; i < size; i++)
        *(int*)(dest + i) = data;

    return dest;
}

void* memcpy(void* source, const void* dest, size_t size) {
    for (size_t i = 0; i < size; i++)
        *(int*)(source + i) = *(int*)(dest + i);

    return source;
}
