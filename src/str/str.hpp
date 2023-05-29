#ifndef _CORE_STRH
#define _CORE_STRH

#include "../types/types.hpp"

//! Returns the length of a string in characters (excludes null byte).
size_t strlen(const char* str);

//! Copies a string from one place to another.
char *strcpy(const char *source, char *dest);

#endif