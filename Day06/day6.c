#include "day6.h"

#include <assert.h>
#include <string.h>

Map map_init(DawnStringBuilder map_content) {
    Map map = {0};

    char delim[] = "\n";
    char *token = strtok(map_content.items, delim);
    while (token) {
        DAWN_DA_APPEND(&map, token);
        token = strtok(NULL, delim);
    }

    map.width = strlen(map.items[0]);

    return map;
}

void map_free(Map map) {
    DAWN_SB_FREE(map);
}

size_t count_unique_positions(Map map) {
    size_t count = 0;
    for (size_t y = 0; y < map.length; y++) {
        for (size_t x = 0; x < map.width; x++) {
            if (map.items[y][x] == 'X') count++;
        }
    }
    return count;
}

void map_print(Map map) {
    for (size_t y = 0; y < map.length; y++) {
        for (size_t x = 0; x < map.width; x++) {
            printf("%c", map.items[y][x]);
        }
        putchar('\n');
    }
    putchar('\n');
}

Guard guard_init(Map map) {
    Guard guard = {0};
    for (size_t y = 0; y < map.length; y++) {
        for (size_t x = 0; x < map.width; x++) {
            if (map.items[y][x] == '^') {
                guard.x = x;
                guard.y = y;
                guard.d = UP;
            }
        }
    }
    return guard;
}

static bool can_move(Guard *guard, Map map) {
    switch (guard->d) {
    case UP:
        return guard->y == 0 || (guard->y > 0 && map.items[guard->y - 1][guard->x] != '#');
    case RIGHT:
        return guard->x == map.width - 1 || (guard->x < map.width - 1 && map.items[guard->y][guard->x + 1] != '#');
    case DOWN:
        return guard->y == map.length - 1 || (guard->y < map.length - 1 && map.items[guard->y + 1][guard->x] != '#');
    case LEFT:
        return guard->x == 0 || (guard->x > 0 && map.items[guard->y][guard->x - 1] != '#');
    default:
        assert(0 && "Unreachable");
    }
}

static inline void turn_right(Guard *guard) {
    guard->d = dawn_mod(guard->d + 1, DIRECTION_MAX);
}

static void move(Guard *guard, Map map) {
    map.items[guard->y][guard->x] = 'X';
    switch (guard->d) {
    case UP:
        guard->y -= 1;
        break;
    case RIGHT:
        guard->x += 1;
        break;
    case DOWN:
        guard->y += 1;
        break;
    case LEFT:
        guard->x -= 1;
        break;
    default:
        assert(0 && "Unreachable");
    }
}

bool guard_step(Guard *guard, Map map) {
    while (!can_move(guard, map)) {
        turn_right(guard);
    }
    move(guard, map);
    return guard->x >= map.width || guard->y >= map.length;
}
