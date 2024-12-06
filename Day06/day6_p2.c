#include "day6.h"

#define DAWN_IMPLEMENTATION
#include "../dawn_utils.h"

typedef struct {
    size_t map_width;
    size_t map_length;
    size_t guard_x;
    size_t guard_y;
} Info;

DawnStringBuilder get_map_content(const char *fp) {
    DawnStringBuilder map_content = {0};
    if (!dawn_read_entire_file(fp, &map_content)) {
        return map_content;
    }
    DAWN_SB_APPEND_BUF(&map_content, "", 1);
    return map_content;
}

DawnStringBuilder sb_clone(DawnStringBuilder sb) {
    DawnStringBuilder clone = {0};
    DAWN_SB_APPEND_BUF(&clone, sb.items, sb.length);
    return clone;
}

Info get_info(DawnStringBuilder map_content) {
        DawnStringBuilder map_content_clone = sb_clone(map_content);
        Map map = map_init(map_content_clone);
        Guard guard = guard_init(map);

        Info info = {
            .map_width = map.width,
            .map_length = map.length,
            .guard_x = guard.x,
            .guard_y = guard.y,
        };

        map_free(map);
        DAWN_SB_FREE(map_content_clone);

        return info;
}

int main(int argc, char **argv) {
    char *program = dawn_shift_args(&argc, &argv);
    if (argc == 0) {
        printf("Usage: %s <map.txt>\n", program);
        return 1;
    }

    char *fp = dawn_shift_args(&argc, &argv);

    DawnStringBuilder map_content_original = get_map_content(fp);
    if (map_content_original.capacity == 0) return 1;

    Info info = get_info(map_content_original);

    size_t potential_position_count = 0;
    for (size_t y = 0; y < info.map_length; y++) {
        for (size_t x = 0; x < info.map_width; x++) {
            if ((x == info.guard_x && y == info.guard_y) || map_content_original.items[(info.map_width + 1) * y + x] == '#') continue;

            DawnStringBuilder map_content = sb_clone(map_content_original);

            Map map = map_init(map_content);
            Guard guard = guard_init(map);

            map.items[y][x] = '#';

            size_t steps_taken = 0;
            while (!guard_step(&guard, map) && steps_taken < info.map_length * info.map_width) steps_taken++;

            if (steps_taken == info.map_length * info.map_width) potential_position_count++;

            map_free(map);
            DAWN_SB_FREE(map_content);
        }
    }

    printf("Number of potential positions: %zu\n", potential_position_count);

    DAWN_SB_FREE(map_content_original);

    return 0;
}
