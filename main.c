#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "hash_map.h"

int main(int argc, char** argv) {
    hash_map* map = create_hash_map_str("aaahi", "ok mon pote !");
    char* b = (char*)delete_hash_map_str(map, "aaahi", 0);
    printf("%s", b);
    return 0;
}