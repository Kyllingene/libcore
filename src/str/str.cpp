#include "str.hpp"
#include "../mem/mem.hpp"

size_t strlen(const char* str) {
    size_t i = 0;
    while (str[i])
        i++;

    return i;
}

char *strcpy(const char *source, char *dest) {
    size_t i;
    for (i = 0; source[i]; i++)
        dest[i] = source[i];

    dest[i] = 0;
    return dest;
}
