#ifndef _CORE_POINTERH
#define _CORE_POINTERH

#include "../cralloc/cralloc.hpp"

template<class T>
class Pointer {
    T* data;

    public:
        Pointer(T* obj) {
            data = obj;
        }

        //! Get a pointer to the underlying data.
        T* deref() {
            return data;
        }

        ~Pointer() {
            T obj = *data;
            cree(data);
        }
};

#endif
