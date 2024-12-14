#include "day14.h"

#define DAWN_IMPLEMENTATION
#include "../dawn_utils.h"

#include <stdio.h>

#define SECONDS 100

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

    size_t q1_count = 0;
    size_t q2_count = 0;
    size_t q3_count = 0;
    size_t q4_count = 0;

    for (Robot *it = rs.items; (size_t)(it - rs.items) < rs.length; it++) {
        robot_move(it, size, SECONDS);

        if (it->px < size.width / 2 && it->py < size.height / 2) {
            q1_count++;
        } else if (it->px > size.width / 2 && it->py < size.height / 2) {
            q2_count++;
        } else if (it->px < size.width / 2 && it->py > size.height / 2) {
            q3_count++;
        } else if (it->px > size.width / 2 && it->py > size.height / 2) {
            q4_count++;
        }
    }

    printf("Safety factor: %zu\n", q1_count * q2_count * q3_count * q4_count);

    robots_free(rs);

    return 0;
}
