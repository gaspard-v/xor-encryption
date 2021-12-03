#include <stdlib.h>
#include "hash_map.h"
#define XOR_HASH 0x12

static uint64_t get_hash(size_t key_size, void* key)
{
    char* _key = (char*)key;
    uint64_t hash = 0UL;
    uint64_t transform = 0UL;
    const uint8_t hash_length = sizeof(uint64_t);
    for(size_t i = 0 ; i < key_size ; i++)
    {
        transform = (_key[i] ^ XOR_HASH);
        transform = transform << ((i%hash_length) * 8);
        hash ^= transform ;
    }
    return hash;
}

hash_map* create_hash_map(size_t key_size, void* restrict key, void* restrict value) {
    hash_map* hashmap = calloc(1, sizeof(hash_map));
    hashmap->bytes = value;
    hashmap->hash = get_hash(key_size, key);
    hashmap->next = NULL;
    return hashmap;
}

uint8_t add_hash_map(hash_map* hashmap, size_t key_size,
                     void* restrict key, void* restrict value)
{
    if (hashmap == NULL) return 0;
    hash_map* current_map = hashmap;
    uint64_t key_hash = get_hash(key_size, key);
    for(;;)
    {
        if(key_hash == current_map->hash)
            return 0;
        if(current_map->next == NULL)
            break;
        current_map = current_map->next;
    }
    current_map->next = calloc(1, sizeof(hash_map));
    current_map->next->hash = key_hash;
    current_map->next->bytes = value;
    current_map->next->next = NULL;
    return 1;
}

void* get_hash_map(hash_map* hashmap, size_t key_size, void* key)
{
    hash_map* current_map = hashmap;
    uint64_t key_hash = get_hash(key_size, key);
    for(;current_map != NULL;)
    {
        if(current_map->hash == key_hash)
            return current_map->bytes;
        current_map = current_map->next;
    }
    return NULL;
}

void free_hash_map(hash_map* hashmap, uint8_t do_free)
{
    hash_map* current_map = hashmap;
    hash_map* next_map = NULL;
    for(;current_map != NULL;)
    {
        next_map = current_map->next;
        if(current_map->bytes != NULL && do_free)
            free(current_map->bytes);
        free(current_map);
        current_map = next_map;
    }
    hashmap = NULL;
}

void* delete_hash_map(hash_map* hashmap, size_t key_size, 
                      void* key, uint8_t do_free)
{
    hash_map* current_map = hashmap;
    hash_map* previous_map = NULL;
    uint64_t key_hash = get_hash(key_size, key);
    void* byte_return = NULL;
    for(;current_map != NULL;)
    {
        if(current_map->hash == key_hash)
        {
            if(do_free)
                free(current_map->bytes);
            else
                byte_return = current_map->bytes;
            if(previous_map != NULL)
                previous_map = current_map->next;
            free(current_map);
            return byte_return;
        }
        previous_map = current_map;
        current_map = current_map->next;
    }
    return NULL;
}

uint8_t create_or_add_hash_map(hash_map** hashmap, size_t key_size, 
                                 void* restrict key, void* restrict value)
{
    if(*hashmap == NULL)
    {
        *hashmap = create_hash_map(key_size, key, value);
        return (*hashmap == NULL) ? 0 : 1 ;
    }
    return add_hash_map(*hashmap, key_size, key, value);
}