#include "math.hpp"

namespace core {

    size_t pow(size_t x, size_t exp) {
        if (exp == 0)
            return 1;
        else if (exp == 1)
            return x;
        
        for (; exp > 0; exp--)
            x *= x;

        return x;
    }

}
