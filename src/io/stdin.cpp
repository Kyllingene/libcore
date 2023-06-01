#include "io.hpp"
#include "../cralloc/cralloc.hpp"

namespace core {
    
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
            throw "failed to allocate space for getl";

        size_t i = 0;
        size_t size = 8;
        size_t used;
        while (true) {
            size_t oldi = i;
            size_t r = read(0, buf+i, size-i);
            if (r == -1)
                throw "failed to read from stdin for getl";

            i += r;

            if (i == size) {
                size *= 2;
                buf = (char*)crealloc(buf, size);
                if (!buf)
                    throw "failed to allocate more space for getl";
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
        if (!buf)
            throw "failed to resize space for getl";

        buf[used] = 0;
        return buf;
    }

}
