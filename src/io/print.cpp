#include "print.hpp"
#include "../str/str.hpp"
extern "C" int _print(const char* str, size_t len);

void printl(const char* str, size_t len) {
    _print(str, len);
}

void print(const char* str) {
    _print(str, strlen(str));
}
