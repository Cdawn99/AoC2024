#ifndef DAY14_H_
#define DAY14_H_

#include "../dawn_utils.h"

#include <stddef.h>
#include <stdint.h>

typedef struct {
    int64_t width;
    int64_t height;
} RoomSize;

RoomSize room_size_init(char *info);

typedef struct {
    int64_t px;
    int64_t py;
    int64_t vx;
    int64_t vy;
} Robot;

void robot_move(Robot *r, RoomSize size, size_t seconds);

typedef struct {
    size_t length;
    size_t capacity;
    Robot *items;
} Robots;

Robots robots_init(DawnStringBuilder info);
void robots_free(Robots rs);

#endif // DAY14_H_
