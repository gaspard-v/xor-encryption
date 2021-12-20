#ifndef FILE_IO_H
#define FILE_IO_H
#define DEFAULT_BLOCK_SIZE 4096
#include <stdint.h>
#include <stdio.h>
uint8_t encrypt_file(FILE* file, size_t key_size, char* key ,size_t block_size);
#endif