#include "io.hpp"

extern "C" filed _open(const char* filename, int flags, int mode);
extern "C" void _close(filed fd);
extern "C" ssize_t _read(filed fd, char* buf, size_t count);
extern "C" ssize_t _write(filed fd, const char* buf, size_t count);

filed open(const char* filename, int flags, int mode) {
    if (mode < 0)
        mode = O_DMODE;
    return _open(filename, flags, mode);
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
