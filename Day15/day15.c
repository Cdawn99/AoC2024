#include "day15.h"

#include <stdbool.h>
#include <string.h>

Map map_init(DawnStringBuilder content) {
    Map map = {0};

    char delim[] = "\n";
    char *token = strtok(content.items, delim);
    while (token) {
        DAWN_DA_APPEND(&map, token);
        token = strtok(NULL, delim);
    }
    map.width = strlen(map.items[0]);

    return map;
}

void map_free(Map map) {
    DAWN_DA_FREE(map);
}

void map_print(Map map) {
    for (size_t y = 0; y < map.length; y++) {
        for (size_t x = 0; x < map.width; x++) {
            putchar(map.items[y][x]);
        }
        putchar('\n');
    }
}

size_t sum_of_box_gps_coords(Map map) {
    size_t sum = 0;
    for (size_t y = 1; y < map.length - 1; y++) {
        for (size_t x = 1; x < map.width - 1; x++) {
            if (map.items[y][x] == 'O') sum += 100 * y + x;
        }
    }
    return sum;
}

size_t wide_sum_of_box_gps_coords(Map map) {
    size_t sum = 0;
    for (size_t y = 1; y < map.length - 1; y++) {
        for (size_t x = 1; x < map.width - 1; x++) {
            if (map.items[y][x] == '[') sum += 100 * y + x;
        }
    }
    return sum;
}

Robot robot_init(Map map) {
    for (size_t y = 1; y < map.length - 1; y++) {
        for (size_t x = 1; x < map.width - 1; x++) {
            if (map.items[y][x] == '@') {
                return (Robot){.x = x, .y = y};
            }
        }
    }
    return (Robot){0};
}

void robot_step(Robot *robot, Map map, char instruction) {
    Vector dir = {0};
    switch (instruction) {
    case '^':
        dir.y = -1;
        break;
    case '<':
        dir.x = -1;
        break;
    case 'v':
        dir.y = 1;
        break;
    case '>':
        dir.x = 1;
        break;
    }

    Vector empty_pos = {.x = robot->x, .y = robot->y};
    while (map.items[empty_pos.y][empty_pos.x] != '.' && map.items[empty_pos.y][empty_pos.x] != '#') {
        empty_pos.x += dir.x;
        empty_pos.y += dir.y;
    }
    if (map.items[empty_pos.y][empty_pos.x] == '#') return;

    while (map.items[empty_pos.y + dir.y][empty_pos.x + dir.x] != '@') {
        char temp = map.items[empty_pos.y - dir.y][empty_pos.x - dir.x];
        map.items[empty_pos.y - dir.y][empty_pos.x - dir.x] = map.items[empty_pos.y][empty_pos.x];
        map.items[empty_pos.y][empty_pos.x] = temp;

        empty_pos.x -= dir.x;
        empty_pos.y -= dir.y;
    }

    robot->x += dir.x;
    robot->y += dir.y;
}

static bool register_boxes_to_move(BoxPositions *bps, Map map, size_t idx, Vector dir) {
    if (idx >= bps->length) return true;

    Vector it = bps->items[idx];

    Vector candidates[2] = {0};

    if (dir.x == 0) {
        candidates[0] = (Vector){
            .x = it.x,
            .y = it.y + dir.y,
        };
        candidates[1] = (Vector){
            .x = it.x + 1,
            .y = it.y + dir.y,
        };
    } else {
        candidates[0] = (Vector){
            .x = it.x + dir.x,
            .y = it.y,
        };
    }

    if (map.items[candidates[0].y][candidates[0].x] == '#') return false;

    if (map.items[candidates[0].y][candidates[0].x] != '.') {
        if (map.items[candidates[0].y][candidates[0].x] == ']') candidates[0].x--;
        DAWN_DA_APPEND(bps, candidates[0]);
    }

    if (candidates[1].x != 0 && candidates[1].y != 0) {
        if (map.items[candidates[1].y][candidates[1].x] == '#') return false;

        if (map.items[candidates[1].y][candidates[1].x] != '.') {
            if (map.items[candidates[1].y][candidates[1].x] == ']') candidates[1].x--;
            DAWN_DA_APPEND(bps, candidates[1]);
        }
    }

    return register_boxes_to_move(bps, map, idx + 1, dir);
}

void move_boxes(BoxPositions *bps, Map map, Vector dir) {
    for (size_t i = bps->length - 1; i < bps->length; i--) {
        Vector it = bps->items[i];

        map.items[it.y + dir.y][it.x + dir.x] = '[';
        map.items[it.y + dir.y][it.x + dir.x + 1] = ']';

        if (dir.x == 0) {
            map.items[it.y][it.x] = '.';
            map.items[it.y][it.x + 1] = '.';
        } else {
            if (dir.x > 0) {
                map.items[it.y][it.x] = '.';
            } else {
                map.items[it.y][it.x + 1] = '.';
            }
        }
    }
}

void wide_robot_step(Robot *robot, BoxPositions *bps, Map map, char instruction) {
    Vector dir = {0};
    switch (instruction) {
    case '^':
        dir.y = -1;
        break;
    case '<':
        dir.x = -1;
        break;
    case 'v':
        dir.y = 1;
        break;
    case '>':
        dir.x = 1;
        break;
    }

    if (map.items[robot->y + dir.y][robot->x + dir.x] == '#') return;
    if (map.items[robot->y + dir.y][robot->x + dir.x] == '.') goto move_robot;

    Vector candidate = {
        .x = robot->x + dir.x,
        .y = robot->y + dir.y,
    };
    if (map.items[candidate.y][candidate.x] == ']') candidate.x--;
    DAWN_DA_APPEND(bps, candidate);

    Vector box_dir = dir;
    if (box_dir.x > 0) box_dir.x *= 2;

    if (!register_boxes_to_move(bps, map, 0, box_dir)) return;
    move_boxes(bps, map, dir);

move_robot:
    map.items[robot->y + dir.y][robot->x + dir.x] = '@';
    map.items[robot->y][robot->x] = '.';

    robot->x += dir.x;
    robot->y += dir.y;
}
