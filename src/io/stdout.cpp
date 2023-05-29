#include "io.hpp"
#include "../str/str.hpp"
extern "C" int _write(int fd, const char* str, size_t len);

void printl(const char* str, size_t len) {
    _write(1, str, len);
}

void print(const char* str) {
    _write(1, str, strlen(str));
}

void putch(char ch) {
    _write(1, &ch, 1);
}
