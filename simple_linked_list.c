#include "simple_linked_list.h"
#include <stdlib.h>
simple_linked_list* create_simple_linked_list(void* data)
{
    simple_linked_list* list = calloc(1, sizeof(simple_linked_list));
    list->data = data;
    list->next = NULL;
    return list;
}

uint8_t add_simple_node(simple_linked_list* list, void* data)
{
    simple_linked_list* current_list = list;
    for(;current_list->next != NULL;)
    {
        current_list = current_list->next;
    }
    current_list->next = calloc(1, sizeof(simple_linked_list));
    if(current_list->next == NULL)
        return 0;
    current_list->next->data = data;
    current_list->next->next = NULL;
    return 1;
}

void* get_simple_node(simple_linked_list* list, uint32_t position)
{
    simple_linked_list* current_list = list;
    for(uint32_t i = 0 ; current_list != NULL ; i++)
    {
        if(i == position)
            return current_list->data;
    }
    return NULL;
}
void* get_last_simple_node(simple_linked_list* list)
{
    simple_linked_list* current_list = list;
    if(list == NULL)
        return NULL;
    for(;current_list->next != NULL;)
    {
        current_list = current_list->next;
    }
    return current_list->data;
}
void* delete_simple_node(simple_linked_list* list, uint32_t position)
{
    simple_linked_list* current_list = list;
    simple_linked_list* previous_list = NULL;
    void* data_return = NULL;
    for(uint32_t i = 0 ;current_list != NULL; i++)
    {
        if(i == position)
        {
            if(previous_list != NULL)
            {
                previous_list->next = current_list->next;
            }
            data_return = current_list->data;
            free(current_list);
            return data_return;
        }
        previous_list = current_list;
        current_list = current_list->next;
    }
    return NULL;
}

void* foreach_simple_node(simple_linked_list* list, 
                          simple_linked_list** current_list, 
                          uint32_t* idx)
{
    if(*idx == 0)
    {
        *current_list = list;
    } else {
        *current_list = (*current_list)->next;
        if(*current_list == NULL)
            return NULL;
    }
    (*idx)++;
    return (*current_list)->data;
}

uint8_t coa_simple_linked_list(simple_linked_list** list, void* data)
{
    if(*list == NULL)
    {
        *list = create_simple_linked_list(data);
        return (*list)? 1 : 0;
    }
    return add_simple_node(*list, data);
}