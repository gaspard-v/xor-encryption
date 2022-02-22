#include <stdlib.h>
#include "hash_map.h"
#define XOR_HASH 0x12

static uint64_t get_hash(size_t key_size, void* key);
static hash_map* get_hash_map_obj(hash_map* hashmap, size_t key_size, void* key);
static uint8_t free_itself(void* data);


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

static hash_map* get_hash_map_obj(hash_map* hashmap, size_t key_size, void* key) {
    hash_map* current_map = hashmap;
    uint64_t key_hash = get_hash(key_size, key);
    for(;current_map != NULL;)
    {
        if(current_map->hash == key_hash)
            return current_map;
        current_map = current_map->next;
    }
    return NULL;
}

static uint8_t free_itself(void* data)
{
    free(data);
    return 1;
}

hash_map* create_hash_map(size_t key_size, 
                          void* restrict key,
                          size_t value_size, 
                          void* restrict value,
                          uint8_t deepcopy,
                          uint8_t (*free_callback)(void*))
{
    hash_map* hashmap = calloc(1, sizeof(hash_map));
    if(deepcopy)
    {
        hashmap->bytes = malloc(value_size);
        if(hashmap->bytes == NULL)
            return NULL;
        memcpy(hashmap->bytes, value, value_size);
        hashmap->free_callback = free_itself;
    }
    else if(free_callback)
    {
        hashmap->bytes = value;
        hashmap->free_callback = free_callback;
    } else {
        hashmap->bytes = value;
        hashmap->free_callback = NULL;
    }
    hashmap->hash = get_hash(key_size, key);
    hashmap->next = NULL;
    return hashmap;
}

uint8_t add_hash_map(hash_map* hashmap, 
                     size_t key_size,
                     void* restrict key,
                     size_t value_size, 
                     void* restrict value,
                     uint8_t deepcopy,
                     uint8_t (*free_callback)(void*))
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
    if(current_map->next == NULL)
        return 0;
    current_map->next->hash = key_hash;
    if(deepcopy)
    {
        current_map->next->bytes = malloc(value_size);
        if(current_map->next->bytes == NULL)
            return 0;
        memcpy(current_map->next->bytes, value, value_size);
        current_map->next->free_callback = free_itself;
    }
    else if(free_callback)
    {
        current_map->next->bytes = value;
        current_map->next->free_callback = free_callback;
    } else {
        current_map->next->bytes = value;
        current_map->next->free_callback = NULL;
    }
    current_map->next->next = NULL;
    return 1;
}

void* get_hash_map(hash_map* hashmap, size_t key_size, void* key)
{
    hash_map* hashmap_t = get_hash_map_obj(hashmap, key_size, key);
    if(hashmap_t == NULL)
        return NULL;
    return hashmap_t->bytes;
}

void free_hash_map(hash_map* hashmap)
{
    hash_map* current_map = hashmap;
    hash_map* next_map = NULL;
    for(;current_map != NULL;)
    {
        next_map = current_map->next;
        if(current_map->free_callback != NULL)
            current_map->free_callback(current_map->bytes);
        free(current_map);
        current_map = next_map;
    }
    hashmap = NULL;
}

void* delete_hash_map(hash_map* hashmap, 
                      size_t key_size, 
                      void* key, 
                      uint8_t auto_free)
{
    hash_map* current_map = hashmap;
    hash_map* previous_map = NULL;
    uint64_t key_hash = get_hash(key_size, key);
    void* byte_return = NULL;
    for(;current_map != NULL;)
    {
        if(current_map->hash == key_hash)
        {
            if(auto_free && current_map->free_callback)
                current_map->free_callback(current_map->bytes);
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

uint8_t create_or_add_hash_map(hash_map** hashmap, 
                               size_t key_size, 
                               void* restrict key,
                               size_t value_size, 
                               void* restrict value,
                               uint8_t deepcopy,
                               uint8_t (*free_callback)(void*))
{
    if(*hashmap == NULL)
    {
        *hashmap = create_hash_map(key_size, key, value_size ,value, deepcopy, free_callback);
        return (*hashmap == NULL) ? 0 : 1 ;
    }
    return add_hash_map(*hashmap, key_size, key, value_size ,value, deepcopy, free_callback);
}

void* modify_hash_map(hash_map* hashmap, 
                      size_t key_size, 
                      void* restrict key,
                      size_t value_size, 
                      void* restrict value,
                      uint8_t auto_free,
                      uint8_t deepcopy,
                      uint8_t (*free_callback)(void*))
{
    hash_map* hashmap_t = get_hash_map_obj(hashmap, key_size, key);
    if(hashmap_t == NULL)
        return NULL;
    void* bytes_return = (void*)1;
    if(auto_free)
    {
        if(hashmap->free_callback)
            hashmap->free_callback(hashmap->bytes);
    } else {
        bytes_return = hashmap_t->bytes;
    }
    hashmap_t->bytes = NULL;
    if(deepcopy)
    {
        hashmap_t->bytes = malloc(value_size);
        if(hashmap_t->bytes == NULL)
            return NULL;
        memcpy(hashmap_t->bytes, value, value_size);
        hashmap_t->free_callback = free_callback;
    } else if(free_callback) 
    {
        hashmap_t->bytes = value;
        hashmap_t->free_callback = free_itself;
    } else {
        hashmap_t->bytes = value;
        hashmap_t->free_callback = NULL;
    }
    return bytes_return;
}
