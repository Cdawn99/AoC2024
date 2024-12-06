#ifndef DAY6_H_
#define DAY6_H_

#include "../dawn_utils.h"

#include <stdbool.h>
#include <stddef.h>

typedef enum {
    UP,
    RIGHT,
    DOWN,
    LEFT,
    DIRECTION_MAX,
} Direction;

typedef struct {
    size_t width;
    size_t length;
    size_t capacity;
    char **items;
} Map;

Map map_init(DawnStringBuilder map_content);
void map_free(Map map);

size_t count_unique_positions(Map map);
void map_print(Map map);

typedef struct {
    size_t x;
    size_t y;
    Direction d;
} Guard;

Guard guard_init(Map map);

/**
 * @return Whether the guard is off the map.
 */
bool guard_step(Guard *guard, Map map);

#endif // DAY6_H_
