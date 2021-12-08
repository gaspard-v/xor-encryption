#ifndef XOR_CIPHER_H
#define XOR_CIPHER_H
#include <stdint.h>
void* XOR_enc_dec(size_t message_size, void* restrict message, 
                  size_t key_size, void* restrict key);
void* KEY_creation(size_t key_size);
#endif