#ifndef SIMPLE_LINKED_LIST_H
#define SIMPLE_LINKED_LIST_H
#include <stdint.h>
typedef struct simple_linked_list {
    void* data;
    struct simple_linked_list* next;
} simple_linked_list;

simple_linked_list* create_simple_linked_list(void* const data);
uint8_t add_simple_node(simple_linked_list* const restrict list, void* const restrict data);
uint8_t coa_simple_linked_list(simple_linked_list** restrict list, void* const restrict data); //coa = Create Or Add
void* get_simple_node(simple_linked_list* const list, uint32_t position);
void* get_last_simple_node(simple_linked_list* const list);
void* delete_simple_node(simple_linked_list* const list, uint32_t position);
void* foreach_simple_node(simple_linked_list* const restrict list, 
                          simple_linked_list** restrict current_list, 
                          uint32_t* const restrict idx);
uint32_t sizeof_simple_linked_list(simple_linked_list* const list);
#endif