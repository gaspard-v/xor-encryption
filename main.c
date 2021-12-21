#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "file_io.h"

int main(int argc, char** argv) {
    char file[] = "C:/Users/TDGX1277/test.txt";
    char key = 0x3A;
    FILE* file_f = fopen(file, "r+");
    encrypt_file(file_f, 1, &key, DEFAULT_BLOCK_SIZE);
    fclose(file_f);
    return 0;
}