#include "file_io.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "xor_cipher.h"
static size_t get_file_size(FILE* file);

static size_t get_file_size(FILE* file)
{
    if(fseek(file, 0L, SEEK_END))
    {
        perror("Error fseek ");
        exit(1);
    }
    size_t size = 0;
    if(size = ftell(file) == 1L)
    {
        perror("Error ftell ");
        exit(1);
    }
    rewind(file);
    return size;
}

uint8_t encrypt_file(FILE* file, size_t key_size, char* key ,size_t block_size)
{
    char* buffer = calloc(block_size, sizeof(char));
    char* buffer2 = calloc(block_size, sizeof(char));
    if(buffer == NULL || buffer2 == NULL)
        exit(1);
    size_t file_size = get_file_size(file);
    size_t read_pos = 0L;
    size_t read_block = 0L;
    size_t output = 0L;
    for(;;)
    {
        if(read_pos + block_size > file_size)
            read_block = file_size - read_pos;
        else
            read_block = block_size;
        if(!fread(buffer, read_block, 1, file))
        {
            perror("Error fread ");
            exit(1);
        }
        XOR_enc_dec(buffer2, read_block, buffer, key_size, key, read_pos);
        if(fseek(file, read_pos, SEEK_SET))
        {
            perror("Error fseek ");
            exit(1);
        }
        if(!fwrite(buffer2, read_block, 1, file))
        {
            perror("Error fwrite ");
            exit(1);
        }
        read_pos += read_block;
        if(read_pos >= file_size)
            break;
        fseek(file, read_block+1, SEEK_CUR); //TODO modif fseek
    }
    free(buffer2);
    free(buffer);
    return 1;
}