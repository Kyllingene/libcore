#include "mem.hpp"

namespace core {

    void* memset(void* dest, int data, size_t size) {
        for (size_t i = 0; i < size; i++)
            ((char*)dest)[i] = data;

        return dest;
    }

    void* memcpy(const void* source, void* dest, size_t size) {
        for (size_t i = 0; i < size; i++)
            ((char*)dest)[i] = ((char*)source)[i];

        return dest;
    }

}
