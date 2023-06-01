#ifndef _CORE_POINTERH
#define _CORE_POINTERH

#include "../cralloc/cralloc.hpp"

namespace core {

    template<class T>
    class spointer {
        T* data;

    public:
        spointer(T* obj) {
            data = obj;
        }

        ~spointer() {
            T obj = *data;
            cree(data);
        }

        //! Get a pointer to the underlying data.
        T* deref() {
            return data;
        }

        operator T*() {
            return deref();
        }

        operator T**() {
            return &data;
        }

        T operator [](size_t i) {
            return data[i];
        }
    };

}

#endif
