#define DAWN_IMPLEMENTATION
#include "../dawn_utils.h"

#include <string.h>

typedef struct {
    size_t length;
    size_t capacity;
    char **items;
} Map;

Map split_content_to_map(DawnStringBuilder content) {
    Map map = {0};
    char delim[] = "\n";
    char *token = strtok(content.items, delim);
    while (token) {
        DAWN_DA_APPEND(&map, token);
        token = strtok(NULL, delim);
    }
    return map;
}

int main(int argc, char **argv) {
    char *program = dawn_shift_args(&argc, &argv);
    if (argc == 0) {
        printf("Usage: %s <map.txt>\n", program);
        return 1;
    }
    char *fp = dawn_shift_args(&argc, &argv);

    DawnStringBuilder map_content = {0};
    if (!dawn_read_entire_file(fp, &map_content)) {
        return 1;
    }
    DAWN_SB_APPEND_BUF(&map_content, "", 1);

    Map map = split_content_to_map(map_content);

    DAWN_DA_FREE(map);
    DAWN_SB_FREE(map_content);

    return 0;
}
