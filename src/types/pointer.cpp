#include "types.hpp"
#include "../malloc/malloc.hpp"

template<class T>
class Pointer {
    T* data;

    public:
        Pointer(T obj) {
            data = malloc(sizeof(T));
            *data = obj;
        }

        T* deref() {
            return data;
        }

        ~Pointer() {
            delete data;
        }
};
