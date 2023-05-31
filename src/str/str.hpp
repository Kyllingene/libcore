#ifndef _CORE_STRH
#define _CORE_STRH

#include "../types/types.hpp"
#include "../cralloc/cralloc.hpp"
#include "../mem/mem.hpp"

//! Returns the length of a string in characters (excludes null byte).
size_t strlen(const char* str);

//! Copies a string from one place to another.
char *strcpy(const char *source, char *dest);

//! Reverses a string inplace.
void reverse(char* str, size_t length);

//! Formats an integer into a string.
char* itoa(ssize_t value, int radix);

//! Formats a pointer into a string.
char* ptoa(void* value);

//! Formats a double into a string.
char* ftoa(double value);

#endif