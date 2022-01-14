#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include "file_io.h"

int main(int argc, char** argv) {
    char file[] = "C:/Users/TDGX1277/test.txt";
    char key = 0x3A;
    FILE* file_f = fopen(file, "r+");
    if (file_f == NULL)
    {
        //cannot open the file !
        fprintf(stderr, "Cannot open %s file. errno: %d", file, errno);
        return -1;
    }
    encrypt_file(file_f, 1, &key, DEFAULT_BLOCK_SIZE);
    int returnCode = fclose(file_f);
    if (returnCode == EOF)
    {
        fprintf(stderr, "Cannot close %s file. errno: %d", file, errno);
        return -1;
    }
    return 0;
}