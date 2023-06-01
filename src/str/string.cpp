#include "string.hpp"

namespace core {

    string::string() {
        data = nullptr;
        len = 0;
        cap = 0;
    }

    string::string(char* str) {
        len = strlen(str);
        cap = len;
        data = (char*)cralloc(cap);
        if (!data)
            throw "failed to allocate space for string";

        memcpy(str, data, cap);
    }

    string::string(size_t length) {
        len = length;
        cap = len;
        data = (char*)cralloc(cap);
        if (!data)
            throw "failed to allocate space for string";
    }

    string::string(char* str, size_t length) {
        len = length;
        cap = len;
        data = (char*)cralloc(cap);
        if (!data)
            throw "failed to allocate space for string";

        memcpy(str, data, cap);
    }

    string::~string() {
        cree(data);
    }

    char* string::cstr() {
        return data;
    }

    size_t string::length() {
        return len;
    }

    size_t string::push(char ch) {
        if (len == cap) {
            if (!cap)
                cap = 8;
            else
                cap *= 2;

            data = (char*)crealloc(data, cap);
            if (!data)
                throw "failed to allocate more space for string";
        }

        data[len] = ch;
        return ++len;
    }

    size_t string::append(const char* str) {
        size_t newlen = strlen(str) + len;
        if (newlen >= cap) {
            if (!cap)
                cap = 8;
            else
                cap *= 2;

            data = (char*)crealloc(data, cap);
            if (!data)
                throw "failed to allocate more space for string";
        }

        strcpy(str, (char*)(size_t)data + len); // NOLINT data's size is guaranteed
        len = newlen;
        return len;
    }

    void string::clear() {
        memset(data, 0, len);
    }

    void string::clear(size_t length) {
        memset(data, 0, len);
        len = 0;
        cap = length;
        data = (char*)crealloc(data, 0);
        if (!data)
            throw "failed to resize string";
    }

    string* string::operator <<(char ch) {
        push(ch);
        return this;
    }

    string* string::operator <<(const char* str) {
        append(str);
        return this;
    }

    char string::operator [](size_t i) {
        if (i >= len)
            throw "index out of range of string";
        
        return data[i];
    }

    string::operator char*() {
        return cstr();
    }

}
