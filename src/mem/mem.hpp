#ifndef _CORE_MEMH
#define _CORE_MEMH

#include "../types/types.hpp"

    namespace core {

    //! Set a region of memory to a value.
    void* memset(void* ptr, int data, size_t size);

    //! Copy one region of memory to another.
    void* memcpy(const void* source, void* dest, size_t size);

}

#endif
