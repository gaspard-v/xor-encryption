#ifndef HASH_MAP_H
#define HASH_MAP_H
#include <stdint.h>
#include <string.h>
typedef struct hash_map {
    uint64_t hash;
    void* bytes;
    uint8_t on_heap;
    struct hash_map* next;
} hash_map;

hash_map* create_hash_map(size_t key_size, 
                          void* restrict key,
                          size_t value_size, 
                          void* restrict value,
                          uint8_t on_heap,
                          uint8_t auto_malloc);

uint8_t add_hash_map(hash_map* hashmap, 
                     size_t key_size,
                     void* restrict key,
                     size_t value_size, 
                     void* restrict value,
                     uint8_t on_heap,
                     uint8_t auto_malloc);

void* get_hash_map(hash_map* hashmap, 
                   size_t key_size, 
                   void* key);

void* delete_hash_map(hash_map* hashmap, 
                      size_t key_size, 
                      void* key, 
                      uint8_t auto_free);

void free_hash_map(hash_map* hashmap, uint8_t auto_free);

void* modify_hash_map(hash_map* hashmap, 
                      size_t key_size, 
                      void* restrict key,
                      size_t value_size, 
                      void* restrict value,
                      uint8_t on_heap,
                      uint8_t auto_malloc,
                      uint8_t auto_free);

uint8_t create_or_add_hash_map(hash_map** hashmap, 
                               size_t key_size, 
                               void* restrict key,
                               size_t value_size, 
                               void* restrict value,
                               uint8_t on_heap,
                               uint8_t auto_malloc);




static inline hash_map* create_hash_map_str(char* restrict key,
                                            size_t value_size, 
                                            void* restrict value,
                                            uint8_t on_heap,
                                            uint8_t auto_malloc)
{
    return create_hash_map(strlen(key), (void*)key, value_size ,value, on_heap, auto_malloc);
}

static inline hash_map* create_hash_map_str_auto(char* restrict key,
                                                 size_t value_size,
                                                 void* restrict value)
{
    return create_hash_map(strlen(key), (void*)key, value_size, value, 1, 1);
}

static inline uint8_t add_hash_map_str(hash_map* hashmap, 
                                       char* restrict key,
                                       size_t value_size, 
                                       void* restrict value,
                                       uint8_t on_heap,
                                       uint8_t auto_malloc)
{
    return add_hash_map(hashmap, strlen(key), (void*)key, value_size ,value, on_heap, auto_malloc);
}

static inline uint8_t add_hash_map_str_auto(hash_map* hashmap,
                                            char* restrict key,
                                            size_t value_size,
                                            void* restrict value)
{
    return add_hash_map(hashmap, strlen(key), (void*)key, value_size, value, 1, 1);
}

static inline void* get_hash_map_str(hash_map* hashmap, char* key)
{
    return get_hash_map(hashmap, strlen(key), (void*)key);
}

static inline void* delete_hash_map_str(hash_map* hashmap, char* key, uint8_t auto_free)
{
    return delete_hash_map(hashmap, strlen(key), (void*)key, auto_free);
}

static inline void* delete_hash_map_str_auto(hash_map* hashmap, char* key)
{
    return delete_hash_map(hashmap, strlen(key), (void*)key, 1);
}

static inline uint8_t
create_or_add_hash_map_str(hash_map** hashmap, 
                           char* restrict key,
                           size_t value_size, 
                           void* restrict value,
                           uint8_t on_heap,
                           uint8_t auto_malloc)
{
    return create_or_add_hash_map(hashmap, strlen(key), (void*)key, value_size ,value, on_heap, auto_malloc);
}

static inline uint8_t
create_or_add_hash_map_str_auto(hash_map** hashmap, 
                               char* restrict key,
                               size_t value_size, 
                               void* restrict value)
{
    return create_or_add_hash_map(hashmap, strlen(key), (void*)key, value_size ,value, 1, 1);
}

static inline uint8_t modify_hash_map_str(hash_map* hashmap, 
                                          char* restrict key,
                                          size_t value_size, 
                                          void* restrict value,
                                          uint8_t on_heap,
                                          uint8_t auto_malloc,
                                          uint8_t auto_free)
{
    return (modify_hash_map(hashmap, strlen(key), (void*)key, value_size ,value, on_heap, auto_malloc, auto_free) == NULL) ? 0 : 1;
}

static inline uint8_t modify_hash_map_str_auto(hash_map* hashmap, 
                                               char* restrict key,
                                               size_t value_size, 
                                               void* restrict value)
{
    return (modify_hash_map(hashmap, strlen(key), (void*)key, value_size ,value, 1, 1, 1) == NULL) ? 0 : 1;
}
            
#endif