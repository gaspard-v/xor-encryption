#include "file_io.h"
#include <stdint.h>
#include <stdio.h>
static size_t get_file_size(FILE* file);

static size_t get_file_size(FILE* file)
{
    fseek(file, 0L, SEEK_END);
    size_t size = ftell(file);
    rewind(file);
    return size;
}

uint8_t encrypt_file(FILE* file, size_t key_size, char* key ,size_t block_size)
{
    char* buffer = calloc(block_size, sizeof(char));
    size_t file_size = get_file_size(file);
    size_t read_pos = 0L;
    while(1)
    {

    }
    free(buffer);
}