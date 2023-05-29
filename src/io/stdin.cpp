#include "io.hpp"
#include "../cralloc/cralloc.hpp"
extern "C" ssize_t _read(filed fd, char* buf, size_t count);

char getch() {
    char ch;
    ssize_t res = _read(0, &ch, 1);
    if (res != 1)
        return 0;

    return ch;
}

char* getl() {
    char* buf = (char*)zalloc(8);
    if (!buf)
        return nullptr;

    size_t i = 0;
    size_t size = 8;
    size_t used;
    while (true) {
        size_t oldi = i;
        size_t r = read(0, buf+i, size-i);
        if (r == -1)
            return nullptr;

        i += r;

        if (i == size) {
            size *= 2;
            buf = (char*)crealloc(buf, size);
            if (!buf)
                return nullptr;
        }

        for (size_t j = oldi; j <= i; j++) {
            if (buf[j] == 10) {
                used = j;
                goto eloop;
            }
        }
    }

eloop:
    buf = (char*)crealloc(buf, used+1); // remove excess space
    buf[used] = 0;
    return buf;
}
