#ifndef XOR_CIPHER_H
#define XOR_CIPHER_H
#include <stdint.h>
uint8_t XOR_enc_dec(void * buffer,
                  size_t message_size, 
                  void* restrict message, 
                  size_t key_size, 
                  void* restrict key,
                  size_t offset);
uint8_t KEY_creation(void * buffer, size_t key_size);
#endif