#ifndef DAY15_H_
#define DAY15_H_

#include "../dawn_utils.h"

#include <stddef.h>

typedef struct {
    size_t width;
    size_t length;
    size_t capacity;
    char **items;
} Map;

Map map_init(DawnStringBuilder content);
void map_free(Map map);
void map_print(Map map);

size_t sum_of_box_gps_coords(Map map);
size_t wide_sum_of_box_gps_coords(Map map);

typedef struct {
    size_t x;
    size_t y;
} Robot;

Robot robot_init(Map map);
void robot_step(Robot *robot, Map map, char instruction);

typedef struct {
    int x;
    int y;
} Vector;

typedef struct {
    size_t length;
    size_t capacity;
    Vector *items;
} BoxPositions;

void wide_robot_step(Robot *robot, BoxPositions *bps, Map map, char instruction);

#endif // DAY15_H_
