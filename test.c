#include "test.h"
#include "conversion_utils.h"
#include "base64_utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct func_test {
    uint8_t (* const func_ptr)(void);
    const char func_name[256];
};
static struct func_test func_ptr[FUNC_NB] = {{ .func_ptr = test_byte_to_binary, .func_name = "test bytes to binary string" }, 
                                             { .func_ptr = test_base64_encrypt, .func_name = "test base64 encrypt" },
                                             { .func_ptr = test_base64_decrypt, .func_name = "test base64 decrypt" }};

uint8_t test_base64_decrypt(void)
{
    char test[17] = "QUJDREVGR0hJSg==";
    size_t output_size = 0;
    build_base64_decode_table();
    char* response = (char*)base64_to_byte(&output_size, test);
    int retour = strncmp(response, "ABCDEFGHIJ", 10);
    free(response);
    free_base64_decode_table();
    if(retour || output_size != 10)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

uint8_t test_base64_encrypt(void)
{
    char test[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    size_t output_size = 0;
    char* response = byte_to_base64(10, test, &output_size);
    int retour = strncmp(response, "QUJDREVGR0hJSg==", 17);
    free(response);
    if(retour || output_size != 17)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

uint8_t test_byte_to_binary(void)
{
    char test[10] = "ABCDEFGHI";
    char* response = byte_to_binary(10, test);
    int retour = strncmp(response, "00000000010010010100100001000111010001100100010101000100010000110100001001000001", 10);
    free(response);
    if(retour)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

uint8_t test_main(void)
{
    uint8_t return_code = EXIT_SUCCESS;
    for(uint16_t i ; i < FUNC_NB ; i++)
    {
        printf("%s: ", func_ptr[i].func_name);
        uint8_t retour = func_ptr[i].func_ptr();
        if(retour == EXIT_FAILURE)
        {
            printf("fail !\n");
            return_code = EXIT_FAILURE;
            continue;
        }
        printf("ok\n");
    }
    return return_code;
}

#ifdef ALONE_TEST
int main(int argc, char *argv[])
{
    return test_main();
}
#endif