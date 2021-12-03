#ifndef OPTION_H
#define OPTION_H
#include <stdint.h>
typedef struct option {
    char small_opt[3];
    char* long_opt;
    char* description;
    uint8_t is_optional;
    uint8_t opt_arg;
} option;
void init_opt(void);
void delete_opt(void);
#endif