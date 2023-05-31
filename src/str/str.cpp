#include "str.hpp"

size_t strlen(const char* str) {
    size_t i = 0;
    while (str[i])
        i++;

    return i;
}

char *strcpy(const char *source, char *dest) {
    size_t i;
    for (i = 0; source[i]; i++)
        dest[i] = source[i];

    dest[i] = 0;
    return dest;
}

void reverse(char* str, size_t length)
{
    size_t start = 0;
    size_t end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        end--;
        start++;
    }
}

char* itoa(ssize_t value, int radix) {
    if (!value) {
        char* buf = (char*)zalloc(2);
        if (!buf)
            throw "failed to allocate space for itoa";

        buf[0] = '0';
        return buf;
    }

    bool sign = value < 0;
    if (sign)
        value = -value;

    size_t length = 0;
    size_t size = 16;
    char* buf = (char*)zalloc(size);
    if (!buf)
        throw "failed to allocate space for itoa";

    while (value > 0) {
        int digit = value % radix;
        if (digit < 10)
            buf[length] = '0' + digit;
        else
            buf[length] = 'a' + (digit - 10);

        value /= radix;
        length++;
        if (length == size) {
            size *= 2;
            buf = (char*)crealloc(buf, size);
            if (!buf)
                throw "failed to allocate more space for itoa";
        }
    }

    if (sign) {
        if (length == size) {
            size += 2;
            buf = (char*)crealloc(buf, size);
            if (!buf)
                throw "failed to allocate more space for itoa";

            buf[length++] = '-';
        }
    }

    reverse(buf, length);
    buf[length] = 0;
    return buf;
}

char* ptoa(void* value) {
    size_t v = (size_t)value;
    if (!v) {
        char* buf = (char*)zalloc(6);
        if (!buf)
            throw "failed to allocate space for ptoa";

        strcpy("(nil)", buf); // NOLINT buf's size is guaranteed
        return buf;
    }

    bool sign = v < 0;
    if (sign)
        v = -v;

    size_t length = 0;
    size_t size = 16;
    char* buf = (char*)zalloc(size);
    if (!buf)
        throw "failed to allocate space for ptoa";

    while (v > 0) {
        int digit = v % 16;
        if (digit < 10)
            buf[length] = '0' + digit;
        else
            buf[length] = 'a' + (digit - 10);

        v /= 16;
        length++;
        if (length == size) {
            size *= 2;
            buf = (char*)crealloc(buf, size);
            if (!buf)
                throw "failed to allocate more space for ptoa";
        }
    }

    if (sign) {
        if (length == size) {
            size += 2;
            buf = (char*)crealloc(buf, size);
            if (!buf)
                throw "failed to allocate more space for ptoa";

            buf[length++] = '-';
        }
    }

    reverse(buf, length);
    buf[length] = 0;
    return buf;
}

char* ftoa(double value) {
    if (!value) {
        char* buf = (char*)zalloc(3);
        if (!buf)
            throw "failed to allocate space for ftoa";

        buf[0] = '0';
        buf[1] = '.';
        buf[2] = '0';
        return buf;
    }
    
    char* whole = itoa((ssize_t)value, 10);
    size_t length = strlen(whole);

    bool sign = value < 0;
    if (sign)
        value = -value;

    value -= (size_t)value;
    size_t i = 0;
    while ((ssize_t)value != value && i < 5) {
        value *= 10;
        i++;
    }

    char* decimal = itoa((ssize_t)value, 10);
    char* buf = (char*)crealloc(whole, length + strlen(decimal) + sign + 2);
    if (!buf)
        throw "failed to allocate space for ftoa";

    buf[length++] = '.';
    strcpy(decimal, buf+length); // NOLINT buf's size is guaranteed
    cree(decimal);

    return buf;
}
