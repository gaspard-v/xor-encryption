#include <stdlib.h>
#include <string.h>
#include "base64_utils.h"

#define BASE64_MAX 64
static char byte_to_base64_t[BASE64_MAX] = { 
    'A', 'B','C','D','E','F','G','H','I','J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
    'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a','b','c','d','e','f','g','h','i','j',
    'k','l','m','n','o','p','q','r','s','t',
    'u','v','w','x','y','z','0','1','2','3',
    '4','5','6','7','8','9','+','/'
};

static char* base64_to_byte_t = NULL;

char* byte_to_base64(size_t byte_size, void* bytes, size_t* output_size)
{
    *output_size = 4 * ((byte_size + 2) / 3) + 1;
    char* retour = calloc(*output_size, sizeof(char));
    uint8_t mod_table[] = {0, 2, 1};
    for(size_t i = 0, j = 0 ; i < byte_size ;)
    {
        uint32_t octet_a = i < byte_size ? ((unsigned char*)bytes)[i++] : 0;
        uint32_t octet_b = i < byte_size ? ((unsigned char*)bytes)[i++] : 0;
        uint32_t octet_c = i < byte_size ? ((unsigned char*)bytes)[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        retour[j++] = byte_to_base64_t[(triple >> 3 * 6) & 0x3F];
        retour[j++] = byte_to_base64_t[(triple >> 2 * 6) & 0x3F];
        retour[j++] = byte_to_base64_t[(triple >> 1 * 6) & 0x3F];
        retour[j++] = byte_to_base64_t[(triple >> 0 * 6) & 0x3F];
    }
    for (int i = 0; i < mod_table[byte_size % 3]; i++)
        retour[*output_size - 2 - i] = '=';
    retour[*output_size] = '\0';
    return retour;
}

void* base64_to_byte(size_t* size, char* base64) {
    build_base64_decode_table();
    size_t input_length = strlen(base64);
    *size = input_length / 4 * 3;
    if(base64[input_length - 1] == '=') (*size)--;
    if(base64[input_length - 2] == '=') (*size)--;
    char* retour = calloc(*size, sizeof(char));
    for(size_t i = 0, j = 0 ; i < input_length ;)
    {
        uint32_t triple = 0;
        uint32_t sextet[4] = {0,0,0,0};
        for(;;)
        {
            if(base64[i] != '=' && base64[i] != '\0')
            {
                sextet[i%4] = base64_to_byte_t[(uint8_t)base64[i]];
            } else {
                sextet[i%4] = 0;
            }
            i++;
            if(i%4 == 0 || i == input_length)
                break;
        }
        triple = (sextet[0] << 3 * 6) +
                 (sextet[1] << 2 * 6) +
                 (sextet[2] <<     6) +
                  sextet[3]; 
        if (j < *size) retour[j++] = (triple >> 2 * 8) & 0xFF;
        if (j < *size) retour[j++] = (triple >>     8) & 0xFF;
        if (j < *size) retour[j++] = triple & 0xFF;

    }
    return retour;
}

void build_base64_decode_table(void)
{
    if (base64_to_byte_t != NULL) return;
    base64_to_byte_t = calloc(256, sizeof(char));
    for(size_t i = 0 ; i < BASE64_MAX ; i++)
    {
        base64_to_byte_t[(uint8_t)byte_to_base64_t[i]] = i;
    }
}

void free_base64_decode_table(void)
{
    if (base64_to_byte_t == NULL) return;
    free(base64_to_byte_t);
    base64_to_byte_t = NULL;
}