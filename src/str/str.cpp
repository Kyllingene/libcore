#include "str.hpp"
#include "../mem/mem.hpp"

size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len])
        len++;

    return len;
}

char *strcpy(const char *source, char *dest) {
    return (char*)memcpy((void*)source, dest, strlen(source));
}
