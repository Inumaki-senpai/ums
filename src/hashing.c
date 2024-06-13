
#include <string.h>
#include "hashing.h"

#define SALT "HX4SFD9Y1DSKM0W"
#define TABLESIZE 746921

unsigned long hash(const char *key) {
    unsigned long value = 0, count = 0;

    for (int i = 0; i < strlen(key); i++) {
        value = value * 1921 + key[i];
        if (i > 1)
            value /= key[i-1];
        count += key[i];
    }
    for (int i = 0; i < strlen(SALT); i++) {
        count = count + SALT[i];
        if (key[i] != '\0')
            count += key[i];
    }
    value += count;
    value = value % TABLESIZE;

#undef HASHMAX

    return value;
}
