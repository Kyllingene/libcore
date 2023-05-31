#ifndef _CORE_VECTORH
#define _CORE_VECTORH

#include "../cralloc/cralloc.hpp"

template<class T>
class vector {
    T* data;
    size_t len;
    size_t cap;

public:
    //! Create a new vector with capacity.
    vector(size_t capacity) {
        if (capacity == 0) {
            data = nullptr;
            len = 0;
            cap = 0;
        } else {
            data = (T*)cralloc(capacity * sizeof(T));
            if (!data)
                throw "failed to allocate memory for vector";

            len = 0;
            cap = capacity;
        }
    }

    vector() {
        data = nullptr;
        len = 0;
        cap = 0;
    }

    ~vector() {
        cree(data);
    }

    //! Append a value to a vector. Returns the new length.
    size_t append(T val) {
        if (len == cap) {
            if (!cap)
                cap = 4;
            else
                cap *= 2;
            data = (T*)crealloc(data, cap * sizeof(T));
            if (!data)
                throw "failed to allocate more memory for vector";
        }

        data[len] = val;
        return ++len;
    }

    //! Pop the top value from the vector.
    T pop() {
        if (len == 0)
            throw "tried to pop an empty vector";

        return data[--len];
    }

    //! Insert a value into the vector at index.
    size_t insert(size_t i, T val) {
        if (i == len+1)
            return this->append(val);
        else if (i > len)
            throw "vector insert index out of bounds";

        if (len == cap) {
            cap *= 2;
            data = (T*)crealloc(data, cap * sizeof(T));
            if (!data)
                throw "failed to allocate more memory for vector";
        }

        for (size_t j = len; j >= i; j--)
            memcpy(data[j], data[j+1], sizeof(T));
    
        data[i] = val;
        return ++len;
    }

    //! Remove a value from the vector at index and return it.
    T remove(size_t i) {
        if (i >= len)
            throw "vector remove index out of bounds";

        T val = data[i];

        for (size_t j = i+1; j < len; j++)
            memcpy(data[j], data[j-1], sizeof(T));

        len--;
        return val;
    }

    //! Get the last value from the vector without removing it.
    T last() {
        if (len == 0)
            throw "vector last index out of bounds";

        return data[--len];
    }

    //! Resize the vector to be at least `size`. Returns amount of reserved space.
    size_t reserve(size_t size) {
        if (size < len)
            throw "tried to reserve too little space";

        if (size > cap) {
            cap = size;
            data = (T*)crealloc(data, cap * sizeof(T));
            if (!data)
                throw "failed to allocate more memory for vector";
        }

        return cap;
    }

    //! Return the allocated size of the vector.
    size_t size() {
        return cap;
    }

    //! Return the length of the vector.
    size_t length() {
        return len;
    }

    template<class F>
    void foreach(F func) {
        for (size_t i = 0; i < len; i++)
            func(data[i]);
    }

    size_t operator<<(T val) {
        return this->append(val);
    }

    T operator[](size_t i) {
        if (i > len)
            throw "vector index out of bounds";
    
        return data[i];
    }

    operator T*() {
        return data;
    }
};

#endif
