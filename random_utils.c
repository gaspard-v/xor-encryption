#include "random_utils.h"
#include <stdint.h>
#include <immintrin.h>
char get_random_char(void)
{
    static union {
        uint64_t l;
        char c[sizeof(uint64_t)];
    } random;
    static uint8_t i = 0;
    if(i%sizeof(uint64_t) == 0)
        _rdrand64_step(&(random.l));
    return random.c[i++];
}