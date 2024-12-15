#include "day15.h"

#define DAWN_IMPLEMENTATION
#include "../dawn_utils.h"

#include <stdio.h>
#include <string.h>

char *get_instruction_pointer(char *content) {
    while (*content != '\0' && *(content + 1) != '\0') {
        if (strncmp(content, "\n\n", 2) == 0) {
            return content + 2;
        }
        content++;
    }
    return NULL;
}

int main(int argc, char **argv) {
    char *program = dawn_shift_args(&argc, &argv);
    if (argc == 0) {
        printf("Usage: %s <wide_input.txt>\n", program);
        return 1;
    }

    char *fp = dawn_shift_args(&argc, &argv);
    DawnStringBuilder content = {0};
    if (!dawn_read_entire_file(fp, &content)) return 1;
    DAWN_SB_APPEND_BUF(&content, "", 1);

    char *ip = get_instruction_pointer(content.items);
    if (!ip) {
        puts("Couldn't find instruction pointer.");
        return 1;
    }
    *(ip - 1) = '\0';

    Map map = map_init(content);
    Robot robot = robot_init(map);
    if (robot.x == 0 && robot.y == 0) {
        puts("Couldn't find robot.");
        return 1;
    }

    // map_print(map);
    // putchar('\n');

    BoxPositions bps = {0};
    while (*ip != '\0') {
        wide_robot_step(&robot, &bps, map, *ip);
        bps.length = 0;

        // printf("next ip = %c\n", *ip);

        // char c;
        // scanf("%c", &c);
        // if (c != '\n') break;

        // printf("\x1b[H\x1b[0J");
        // map_print(map);
        // putchar('\n');

        ip++;
        if (*ip == '\n') ip++;
    }

    size_t sum = wide_sum_of_box_gps_coords(map);
    printf("Sum of all boxes' GPS coordinates: %zu\n", sum);

    DAWN_DA_FREE(bps);
    map_free(map);
    DAWN_SB_FREE(content);

    return 0;
}
