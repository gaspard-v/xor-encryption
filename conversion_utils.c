#include <stdlib.h>
#include <stdio.h>
#include "conversion_utils.h"
#define CHAR_MASK 0x01
#define CHAR_BIT_SIZE 0x08
static char int_to_ascii(uint8_t number)
{
    char retour[4];
    snprintf(retour, 4, "%u", number);
    return retour[0];
}

char* byte_to_string(size_t elementSize, void* bytes)
{
    uint32_t const stringSize = (elementSize*CHAR_BIT_SIZE)+1;
    char* retour = calloc(stringSize, sizeof(char));
    uint32_t z = stringSize-2;
    for(size_t i = 0 ; i < elementSize ; i++)
    {
        for(uint8_t y = 0 ; y < CHAR_BIT_SIZE ; y++)
        {
            retour[z--] = int_to_ascii(((((char*)bytes)[i] >> y) & CHAR_MASK));
        }
    }
    retour[stringSize] = '\0';
    return retour;
}