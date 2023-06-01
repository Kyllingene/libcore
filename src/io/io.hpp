#ifndef _CORE_IOH
#define _CORE_IOH

#include "fio.hpp"
#include "../types/types.hpp"
#include "../cralloc/cralloc.hpp"
#include "../str/str.hpp"
#include "../math/math.hpp"

namespace core {

    //! Print a single character.
    void putch(char ch);

    //! Print a string with a length, doesn't need to be null-terminated.
    void printlen(const char* str, size_t len);

    //! Print a valid C string.
    void print(const char* str);

    //! Print a valid C string with a terminating newline.
    void println(const char* str);

    //! Print an integer.
    void printi(ssize_t value, int radix);

    //! Print a float.
    void printd(float value);

    //! Get a single character from stdin.
    char getch();

    //! Read a line from stdin.
    char* getl();

}

#endif
