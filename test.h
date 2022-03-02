#ifndef TEST_H
#define TEST_H
#include <stdint.h>
//#define FUNC_NB 16
#define FUNC_NB 6

//hash map
uint8_t test_creation_hashmap(void);
uint8_t test_filling_hashmap(void);
uint8_t test_wrong_get_hashmap(void);
uint8_t test_correct_get_hashmap(void);
uint8_t test_delete_hashmap(void);
uint8_t test_free_hashmap(void);
uint8_t test_modify_hashmap(void);

//XOR cipher
uint8_t test_xor_cipher(void);
uint8_t test_xor_key_creation(void);

//simple linked list
uint8_t test_create_sl_list(void);
uint8_t test_filling_sl_list(void);
uint8_t test_foreach_sl_list(void);
uint8_t test_size_sl_list(void);


//base64
uint8_t test_base64_encrypt(void);
uint8_t test_base64_decrypt(void);

//conversion
uint8_t test_byte_to_binary(void);

//main
uint8_t test_main(void);

#endif