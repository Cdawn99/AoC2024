#include "day8.h"

#define DAWN_IMPLEMENTATION
#include "../dawn_utils.h"

int main(int argc, char **argv) {
    char *program = dawn_shift_args(&argc, &argv);
    if (argc == 0) {
        printf("Usage: %s <map.txt>\n", program);
        return 1;
    }
    char *fp = dawn_shift_args(&argc, &argv);

    DawnStringBuilder map_content = {0};
    if (!dawn_read_entire_file(fp, &map_content)) return 1;
    DAWN_SB_APPEND_BUF(&map_content, "", 1);

    Map map = map_init(map_content);
    Frequencies freqs = frequencies_init(map);

    for (size_t i = 0; i < freqs.length; i++) {
        mark_antinodes_part_2(map, freqs.items[i]);
    }

    size_t antinode_count = map_count_antinodes(map);
    printf("Number of unique antinodes: %zu\n", antinode_count);

    frequencies_free(freqs);
    map_free(map);
    DAWN_SB_FREE(map_content);

    return 0;
}
