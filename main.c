#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "option.h"

int main(int argc, char** argv) {
    printf("Hello world !\n");
    init_opt(argc, argv);
    return 0;
}