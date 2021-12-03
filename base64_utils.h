#ifndef BASE64_UTILS_H
#define BASE64_UTILS_H
#include <stdint.h>
char* byte_to_base64(size_t byte_size, void* bytes, size_t* output_size);
void* base64_to_byte(size_t* size, char* base64);
void build_base64_decode_table(void);
void free_base64_decode_table(void);
#endif