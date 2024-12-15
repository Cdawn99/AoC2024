#include "day15.h"

#define DAWN_IMPLEMENTATION
#include "../dawn_utils.h"

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
        printf("Usage: %s <input.txt>\n", program);
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

    while (*ip != '\0') {
        robot_step(&robot, map, *ip);
        // map_print(map);
        // putchar('\n');
        ip++;
        if (*ip == '\n') ip++;
    }

    size_t sum = sum_of_box_gps_coords(map);
    printf("Sum of all boxes' GPS coordinates: %zu\n", sum);

    map_free(map);
    DAWN_SB_FREE(content);

    return 0;
}
