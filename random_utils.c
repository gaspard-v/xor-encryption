#include "random_utils.h"
#include <stdint.h>
#include <immintrin.h>
char get_random_char(void)
{
    static union {
        char c[sizeof(long long)];
        unsigned long long l;
    } random;
    static uint8_t i = 0;
    if(i%sizeof(long long) == 0) {
        _rdrand64_step(&(random.l));
        i = 0;
    }
    return random.c[i++];
}