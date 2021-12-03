#ifndef HASH_MAP_H
#define HASH_MAP_H
#include <stdint.h>
#include <string.h>
typedef struct hash_map {
    uint64_t hash;
    void* bytes;
    struct hash_map* next;
} hash_map;

hash_map* create_hash_map(size_t key_size, void* restrict key, void* restrict value);
uint8_t add_hash_map(hash_map* hashmap, size_t key_size,
                     void* restrict key, void* restrict value);
void* get_hash_map(hash_map* hashmap, size_t key_size, void* key);
void* delete_hash_map(hash_map* hashmap, size_t key_size, 
                      void* key, uint8_t do_free);
void free_hash_map(hash_map* hashmap, uint8_t do_free);
uint8_t create_or_add_hash_map(hash_map** hashmap, size_t key_size, 
                                 void* restrict key, void* restrict value);

static inline hash_map* create_hash_map_str(char* restrict key, void* restrict value)
{
    return create_hash_map(strlen(key), key, value);
}
static inline uint8_t add_hash_map_str(hash_map* hashmap, char* restrict key, void* restrict value)
{
    return add_hash_map(hashmap, strlen(key), key, value);
}

static inline void* get_hash_map_str(hash_map* hashmap, char* key)
{
    return get_hash_map(hashmap, strlen(key), key);
}

static inline void* delete_hash_map_str(hash_map* hashmap, char* key, uint8_t do_free)
{
    return delete_hash_map(hashmap, strlen(key), key, do_free);
}

static inline uint8_t
create_or_add_hash_map_str(hash_map** hashmap, 
                           void* restrict key, 
                           void* restrict value)
{
    return create_or_add_hash_map(hashmap, strlen(key), key, value);
}
            
#endif