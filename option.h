#ifndef OPTION_H
#define OPTION_H
#include <stdint.h>

enum opts_type {
    NONE,
    UNIQUE,
    MULTIPLE
};

typedef struct option {
    char small_opt[3];
    char* long_opt;
    char* description;
    uint8_t is_optional;
    enum opts_type opt_arg;
} option;
void init_opt(int argc, char* argv[]);
void free_option_all(void);
#endif