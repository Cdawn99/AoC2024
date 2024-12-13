#ifndef DAY8_H_
#define DAY8_H_

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

size_t map_count_antinodes(Map map);

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    char freq;
    size_t length;
    size_t capacity;
    Point *items;
} Frequency;

void mark_antinodes_part_1(Map map, Frequency freq);
void mark_antinodes_part_2(Map map, Frequency freq);

typedef struct {
    size_t length;
    size_t capacity;
    Frequency *items;
} Frequencies;

Frequencies frequencies_init(Map map);
void frequencies_free(Frequencies freqs);

#endif // DAY8_H_
