#include "day12.h"

#define DAWN_IMPLEMENTATION
#include "../dawn_utils.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    char *program = dawn_shift_args(&argc, &argv);
    if (argc == 0) {
        printf("Usage: %s <map.txt>\n", program);
        return 1;
    }

    char *fp = dawn_shift_args(&argc, &argv);

    DawnStringBuilder map_content = {0};
    if (!dawn_read_entire_file(fp, &map_content)) return 1;

    Map map = map_init(map_content);

    // map_print(map);
    // putchar('\n');

    Points ps = {0};
    Sides sides = {0};
    size_t price = 0;
    bool done = false;
    while (!done) {
        done = false;
        char letter = '#';
        for (size_t y = 0; y < map.length; y++) {
            for (size_t x = 0; x < map.width; x++) {
                if (map.items[y][x] != '#') {
                    letter = map.items[y][x];
                    Point p = {.x = x, .y = y};
                    DAWN_DA_APPEND(&ps, p);
                    goto letter_found;
                }
            }
        }
        done = true;
letter_found:
        price += get_blob_price_part_2(map, letter, &ps, &sides);

        // sides_print(sides);
        // putchar('\n');

        ps.length = 0;
        ps.perimeter = 0;
        sides.length = 0;

        // map_print(map);
        // putchar('\n');
    }

    printf("Price: %zu\n", price);

    DAWN_DA_FREE(sides);
    DAWN_DA_FREE(ps);
    map_free(map);
    DAWN_SB_FREE(map_content);

    return 0;
}
