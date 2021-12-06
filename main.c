#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "simple_linked_list.h"

int main(int argc, char** argv) {
    simple_linked_list* list = create_simple_linked_list("kiejkje");
    add_simple_node(list, "jfejhfhejfehjhj");
    return 0;
}