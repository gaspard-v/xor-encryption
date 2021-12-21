#include "file_io.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "xor_cipher.h"
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
    char* buffer2 = calloc(block_size, sizeof(char));
    if(buffer == NULL || buffer2 == NULL)
        return 0;
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
        fread(buffer, read_block, 1, file); //TODO error
        XOR_enc_dec(buffer2, read_block, buffer, key_size, key, read_pos);
        fseek(file, read_pos, SEEK_SET);
        output = fwrite(buffer2, read_block, 1, file);
        if(!output)
            printf("ERREUR fwrite: %d", errno);
        read_pos += read_block;
        if(read_pos >= file_size)
            break;
        fseek(file, read_block+1, SEEK_CUR); //TODO modif fseek
    }
    free(buffer2);
    free(buffer);
    return 1;
}