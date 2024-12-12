#ifndef DAY12_H_
#define DAY12_H_

#include "../dawn_utils.h"

#include <stddef.h>

typedef struct {
    size_t width;
    size_t length;
    size_t capacity;
    char **items;
} Map;

Map map_init(DawnStringBuilder map_content);
void map_free(Map map);

void map_print(Map map);

typedef struct {
    size_t x;
    size_t y;
} Point;

typedef struct {
    size_t perimeter;
    size_t length;
    size_t capacity;
    Point *items;
} Points;

bool has_point(Points *ps, Point p);

size_t get_blob_price_part_1(Map map, char letter, Points *ps);

typedef enum {
    NORTH,
    WEST,
    SOUTH,
    EAST,
} Direction;

typedef struct {
    size_t var_min;
    size_t var_max;
    size_t stat;
    Direction dir;
} Side;

typedef struct {
    size_t length;
    size_t capacity;
    Side *items;
} Sides;

void sides_print(Sides sides);

size_t get_blob_price_part_2(Map map, char letter, Points *ps, Sides *sides);

#endif // DAY12_H_
