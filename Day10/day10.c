#include "day10.h"

#include <assert.h>
#include <string.h>

Map map_init(DawnStringBuilder map_content) {
    Map map = {0};

    char delim[] = "\n";
    char *token = strtok(map_content.items, delim);
    while (token) {
        DAWN_DA_APPEND(&map, token);
        token = strtok(NULL, delim);
    }

    map.width = strlen(map.items[0]);

    return map;
}

void map_free(Map map) {
    DAWN_SB_FREE(map);
}

void map_print(Map map) {
    for (size_t y = 0; y < map.length; y++) {
        for (size_t x = 0; x < map.width; x++) {
            printf("%c", map.items[y][x]);
        }
        putchar('\n');
    }
    putchar('\n');
}
