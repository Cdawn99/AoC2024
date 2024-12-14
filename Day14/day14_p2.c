#include "day14.h"

#define DAWN_IMPLEMENTATION
#include "../dawn_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERTICAL_INCR 103
#define HORIZONTAL_INCR 101

void display_room(RoomSize size, Robots rs) {
    char *room = malloc((size.width + 1) * size.height + 1);
    memset(room, '.', (size.width + 1) * size.height);
    room[(size.width + 1) * size.height] = '\0';

    for (size_t i = 0; i < (size_t)size.height; i++) {
        room[size.width + i * (size.width + 1)] = '\n';
    }

    for (Robot *it = rs.items; (size_t)(it - rs.items) < rs.length; it++) {
        room[it->py * (size.width + 1) + it->px] = '#';
    }

    puts(room);
    free(room);
}

int main(int argc, char **argv) {
    char *program = dawn_shift_args(&argc, &argv);
    if (argc == 0) {
        printf("Usage: %s <robot_info.txt>\n", program);
        return 1;
    }

    char *fp = dawn_shift_args(&argc, &argv);
    DawnStringBuilder info = {0};
    if (!dawn_read_entire_file(fp, &info)) return 1;
    DAWN_SB_APPEND_BUF(&info, "", 1);

    RoomSize size = room_size_init(info.items);

    Robots rs = robots_init(info);
    DAWN_SB_FREE(info);

    size_t t = 0;

    // printf("t = %zu\n", t);
    // display_room(size, rs);

    // These two potentially depend on input.
    size_t vertical_base = 25;
    size_t horizontal_base = 66;

    char c = '\n';
    // scanf("%c", &c);
    while (c == '\n') {
        while (t != vertical_base && t != horizontal_base) {
            t++;
            for (Robot *it = rs.items; (size_t)(it - rs.items) < rs.length; it++) {
                robot_move(it, size, 1);
            }
        }
        if (t == vertical_base) {
            vertical_base += VERTICAL_INCR;
        } else {
            horizontal_base += HORIZONTAL_INCR;
        }
        printf("t = %zu\n", t);
        display_room(size, rs);
        scanf("%c", &c);
    }

    robots_free(rs);

    return 0;
}
