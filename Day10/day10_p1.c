#include "day10.h"

#define DAWN_IMPLEMENTATION
#include "../dawn_utils.h"

#include <stdbool.h>

typedef struct {
    size_t x;
    size_t y;
} Point;

typedef struct {
    size_t length;
    size_t capacity;
    Point *items;
} Points;

bool has_point(Points *ps, Point p) {
    for (size_t i = 0; i < ps->length; i++) {
        if (ps->items[i].x == p.x && ps->items[i].y == p.y) {
            return true;
        }
    }
    return false;
}

void do_get_trailhead_score(Map map, size_t x, size_t y, Points *visited) {
    if (map.items[y][x] == '9') {
        Point p = {.x = x, .y = y};
        if (!has_point(visited, p)) DAWN_DA_APPEND(visited, p);
        return;
    }
    if (y != 0 && map.items[y][x] + 1 == map.items[y - 1][x]) do_get_trailhead_score(map, x, y - 1, visited);
    if (x != 0 && map.items[y][x] + 1 == map.items[y][x - 1]) do_get_trailhead_score(map, x - 1, y, visited);
    if (y != map.length - 1 && map.items[y][x] + 1 == map.items[y + 1][x]) do_get_trailhead_score(map, x, y + 1, visited);
    if (x != map.width - 1 && map.items[y][x] + 1 == map.items[y][x + 1]) do_get_trailhead_score(map, x + 1, y, visited);
}

size_t get_trailhead_score(Map map, size_t x, size_t y) {
    Points visited = {0};
    do_get_trailhead_score(map, x, y, &visited);
    size_t score = visited.length;
    if (score > 0) DAWN_DA_FREE(visited);
    return score;
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

    Map map = map_init(map_content);

    size_t total_trailhead_score = 0;
    for (size_t y = 0; y < map.length; y++) {
        for (size_t x = 0; x < map.width; x++) {
            if (map.items[y][x] == '0') {
                total_trailhead_score += get_trailhead_score(map, x, y);
            }
        }
    }

    printf("Sum of scores of all trailheads: %zu\n", total_trailhead_score);

    map_free(map);
    DAWN_SB_FREE(map_content);

    return 0;
}
