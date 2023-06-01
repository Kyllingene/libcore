#include "io.hpp"

namespace core {

    extern "C" int _write(int fd, const char* str, size_t len);

    void putch(char ch) {
        _write(1, &ch, 1);
    }

    void printlen(const char* str, size_t len) {
        _write(1, str, len);
    }

    void print(const char* str) {
        _write(1, str, strlen(str));
    }

    void println(const char* str) {
        _write(1, str, strlen(str));
        putch('\n');
    }

    void printi(ssize_t value, int radix) {
        print(itoa(value, radix));
    }

    void printd(float value) {
        print(dtoa(value));
    }

}
