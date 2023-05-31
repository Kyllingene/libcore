#ifndef _CORE_STRINGH
#define _CORE_STRINGH

#include "../types/types.hpp"
#include "../cralloc/cralloc.hpp"
#include "../mem/mem.hpp"
#include "str.hpp"

class string {
    char* data;
    size_t len;
    size_t cap;

public:
    //! Initialize an empty string.
    string();
    //! Initialize a string with data.
    string(char* str);
    //! Initialize a string with a certain capacity.
    string(size_t length);
    //! Initialize a string with data and a specified length.
    string(char* str, size_t length);
    ~string();

    //! Returns a reference to the underlying data.
    char* cstr();
    //! Returns the length of the string.
    size_t length();
    //! Append a character to the string. Returns the new length.
    size_t push(char ch);
    //! Appends a str to the string. Returns the new length.
    size_t append(const char* str);
    //! Clears all data in the string. Doesn't deallocate.
    void clear();
    //! Clears all data in the string and resizes.
    void clear(size_t length);

    size_t operator <<(char ch);
    size_t operator <<(const char* str);
    char operator [](size_t i);
    operator char*();
};

#endif