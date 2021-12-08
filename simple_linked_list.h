#ifndef SIMPLE_LINKED_LIST_H
#define SIMPLE_LINKED_LIST_H
#include <stdint.h>
typedef struct simple_linked_list {
    void* data;
    struct simple_linked_list* next;
} simple_linked_list;

simple_linked_list* create_simple_linked_list(void* data);
uint8_t add_simple_node(simple_linked_list* list, void* data);
uint8_t coa_simple_linked_list(simple_linked_list** list, void* data);
void* get_simple_node(simple_linked_list* list, uint32_t position);
void* get_last_simple_node(simple_linked_list* list);
void* delete_simple_node(simple_linked_list* list, uint32_t position);
void* foreach_simple_node(simple_linked_list* list, 
                          simple_linked_list** current_list, 
                          uint32_t* idx);
uint32_t sizeof_simple_linked_list(simple_linked_list* list);
#endif