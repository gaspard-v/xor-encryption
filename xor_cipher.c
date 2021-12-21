#include <stdlib.h>
#include "xor_cipher.h"
#include "random_utils.h"
uint8_t XOR_enc_dec(void * buffer,
                  size_t message_size, 
                  void* restrict message, 
                  size_t key_size, 
                  void* restrict key,
                  size_t offset)
{
    for(size_t i = offset ; i < message_size ; i++)
    {
        ((char*)buffer)[i] = ((char*)message)[i] ^ ((char*)key)[i%key_size];
    }
    return 1;
}

uint8_t KEY_creation(void * buffer, size_t key_size)
{
    for(size_t i = 0 ; i < key_size ; i++)
    {
        ((char*)buffer)[i] = get_random_char();
    }
    return 1;
}