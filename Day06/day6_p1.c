#include "day6.h"

#define DAWN_IMPLEMENTATION
#include "../dawn_utils.h"

DawnStringBuilder get_map_content(const char *fp) {
    DawnStringBuilder map_content = {0};
    if (!dawn_read_entire_file(fp, &map_content)) {
        return map_content;
    }
    DAWN_SB_APPEND_BUF(&map_content, "", 1);
    return map_content;
}

int main(int argc, char **argv) {
    char *program = dawn_shift_args(&argc, &argv);
    if (argc == 0) {
        printf("Usage: %s <map.txt>\n", program);
        return 1;
    }

    char *fp = dawn_shift_args(&argc, &argv);
    DawnStringBuilder map_content = get_map_content(fp);
    if (map_content.capacity == 0) return 1;

    Map map = map_init(map_content);
    Guard guard = guard_init(map);

    while (!guard_step(&guard, map));

    size_t unique_positions = count_unique_positions(map);
    printf("Number of unique positions: %zu\n", unique_positions);

    map_free(map);
    DAWN_SB_FREE(map_content);

    return 0;
}
