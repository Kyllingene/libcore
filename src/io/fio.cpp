#include "fio.hpp"

namespace core {
    extern "C" filed _open(const char* filename, int flags, int mode);
    extern "C" void _close(filed fd);
    extern "C" ssize_t _read(filed fd, char* buf, size_t count);
    extern "C" ssize_t _write(filed fd, const char* buf, size_t count);

    filed open(const char* filename, int flags, int mode) {
        if (mode < 0)
            mode = O_DMODE;

        return _open(filename, flags, mode);
    }

    filed open(const char* filename, int flags) {
        return open(filename, flags, 0);
    }

    filed create(const char* filename, int mode) {
        if (mode < 0)
            mode = O_DMODE;

        return open(filename, O_CREAT | O_RDWR, mode);
    }

    void close(filed fd) {
        return _close(fd);
    }

    ssize_t read(filed fd, char* buf, size_t count) {
        return _read(fd, buf, count);
    }

    ssize_t write(filed fd, const char* buf, size_t count) {
        return _write(fd, buf, count);
    }

    ofstream::ofstream(const char* filename, int flags, int mode) {
        fd = open(filename, flags, mode);
        if (fd == -1)
            throw "failed to open file for ofstream";
    }

    ofstream::ofstream(filed file) {
        fd = file;
    }

    ofstream::~ofstream() {
        close(fd);
    }

    ofstream ofstream::operator<<(const char* str) {
        if (write(fd, str, strlen(str)) == -1)
            throw "failed to write to file for ofstream";

        return *this;
    }

    ofstream ofstream::operator<<(char ch) {
        if (write(fd, &ch, 1) == -1)
            throw "failed to write to file for ofstream";

        return *this;
    }

    ofstream ofstream::operator<<(ssize_t i) {
        char* str = itoa(i, 10);
        if (!str)
            throw "failed to format integer for ofstream";

        if (write(fd, str, strlen(str)) == -1)
            throw "failed to write to file for ofstream";

        return *this;
    }

    ofstream ofstream::operator<<(int i) {
        return *this << (ssize_t)i;
    }

    ofstream ofstream::operator<<(double d) {
        char* str = dtoa(d);
        if (!str)
            throw "failed to format double for ofstream";

        if (write(fd, str, strlen(str)) == -1)
            throw "failed to write to file for ofstream";

        return *this;
    }

}
