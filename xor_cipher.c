#include <stdlib.h>
#include "xor_cypher.h"
#include "random_utils.h"
void* XOR_enc_dec(size_t message_size, void* restrict message,
                     size_t key_size, void* restrict key)
{
    char* retour = calloc(message_size, sizeof(char));
    for(size_t i = 0 ; i < message_size ; i++)
    {
        retour[i] = ((char*)message)[i] ^ ((char*)key)[i%key_size];
    }
    return (void*)retour;
}

void* KEY_creation(size_t key_size)
{
    char* key = calloc(key_size, sizeof(char));
    for(size_t i = 0 ; i < key_size ; i++)
    {
        key[i] = get_random_char();
    }
    return (void*)key;
}