#include "day12.h"

#include <stdio.h>
#include <stdlib.h>

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
    DAWN_DA_FREE(map);
}

bool has_point(Points *ps, Point p) {
    for (Point *it = ps->items; (size_t)(it - ps->items) < ps->length; it++) {
        if (it->x == p.x && it->y == p.y) return true;
    }
    return false;
}

static size_t do_get_blob_price_part_1(Map map, char letter, Points *ps, size_t pi) {
    if (pi >= ps->length) return ps->length * ps->perimeter;

    Point current = ps->items[pi];

    if (current.y == 0 || map.items[current.y - 1][current.x] != letter) {
        ps->perimeter++;
    } else {
        Point candidate = {.x = current.x, .y = current.y - 1};
        if (!has_point(ps, candidate)) DAWN_DA_APPEND(ps, candidate);
    }

    if (current.x == 0 || map.items[current.y][current.x - 1] != letter) {
        ps->perimeter++;
    } else {
        Point candidate = {.x = current.x - 1, .y = current.y};
        if (!has_point(ps, candidate)) DAWN_DA_APPEND(ps, candidate);
    }

    if (current.y == map.length - 1 || map.items[current.y + 1][current.x] != letter) {
        ps->perimeter++;
    } else {
        Point candidate = {.x = current.x, .y = current.y + 1};
        if (!has_point(ps, candidate)) DAWN_DA_APPEND(ps, candidate);
    }

    if (current.x == map.width - 1 || map.items[current.y][current.x + 1] != letter) {
        ps->perimeter++;
    } else {
        Point candidate = {.x = current.x + 1, .y = current.y};
        if (!has_point(ps, candidate)) DAWN_DA_APPEND(ps, candidate);
    }

    return do_get_blob_price_part_1(map, letter, ps, pi + 1);
}

size_t get_blob_price_part_1(Map map, char letter, Points *ps) {
    if (letter == '#') return 0;

    size_t price = do_get_blob_price_part_1(map, letter, ps, 0);

    for (Point *it = ps->items; (size_t)(it - ps->items) < ps->length; it++) {
        map.items[it->y][it->x] = '#';
    }

    return price;
}

static int compare_sides(const void *s1, const void *s2) {
    const Side *side1 = s1;
    const Side *side2 = s2;

    if (side1->dir > side2->dir) return 1;
    if (side1->dir < side2->dir) return -1;

    if (side1->stat > side2->stat) return 1;
    if (side1->stat < side2->stat) return -1;

    if (side1->var_max < side2->var_min) return -1;
    if (side1->var_min > side2->var_max) return 1;
    return 0;
}

static void register_side(Sides *sides, size_t stat, size_t var, Direction dir) {
    bool found = false;
    if (sides->length != 0) {
        for (Side *it = sides->items; (size_t)(it - sides->items) < sides->length; it++) {
            if (it->dir == dir && it->stat == stat) {
                if (it->var_min - 1 == var) {
                    it->var_min--;
                    found = true;
                } else if (it->var_max + 1 == var) {
                    it->var_max++;
                    found = true;
                }
            }
        }
    }
    if (!found) {
        Side side = {
            .var_min = var,
            .var_max = var,
            .stat = stat,
            .dir = dir,
        };
        DAWN_DA_APPEND(sides, side);
        qsort(sides->items, sides->length, sizeof(*sides->items), compare_sides);
    }
}

static void merge_sides(Sides *sides) {
    for (Side *it = sides->items; (size_t)(it - sides->items) < sides->length - 1; it++) {
        if (it->dir != (it+1)->dir || it->stat != (it+1)->stat) continue;
        while (it->var_max == (it+1)->var_min) {
            (it+1)->var_min = it->var_min;
            size_t move_len = sides->length - (size_t)(it - sides->items + 1);
            memmove(it, it+1, move_len * sizeof(*sides->items));
            sides->length--;
        }
    }
}

static size_t do_get_blob_price_part_2(Map map, char letter, Points *ps, size_t pi, Sides *sides) {
    if (pi >= ps->length) {
        merge_sides(sides);
        return ps->length * sides->length;
    }

    Point current = ps->items[pi];

    if (current.y == 0 || map.items[current.y - 1][current.x] != letter) {
        register_side(sides, current.y, current.x, NORTH);
    } else {
        Point candidate = {.x = current.x, .y = current.y - 1};
        if (!has_point(ps, candidate)) DAWN_DA_APPEND(ps, candidate);
    }

    if (current.x == 0 || map.items[current.y][current.x - 1] != letter) {
        register_side(sides, current.x, current.y, WEST);
    } else {
        Point candidate = {.x = current.x - 1, .y = current.y};
        if (!has_point(ps, candidate)) DAWN_DA_APPEND(ps, candidate);
    }

    if (current.y == map.length - 1 || map.items[current.y + 1][current.x] != letter) {
        register_side(sides, current.y, current.x, SOUTH);
    } else {
        Point candidate = {.x = current.x, .y = current.y + 1};
        if (!has_point(ps, candidate)) DAWN_DA_APPEND(ps, candidate);
    }

    if (current.x == map.width - 1 || map.items[current.y][current.x + 1] != letter) {
        register_side(sides, current.x, current.y, EAST);
    } else {
        Point candidate = {.x = current.x + 1, .y = current.y};
        if (!has_point(ps, candidate)) DAWN_DA_APPEND(ps, candidate);
    }

    return do_get_blob_price_part_2(map, letter, ps, pi + 1, sides);
}

size_t get_blob_price_part_2(Map map, char letter, Points *ps, Sides *sides) {
    if (letter == '#') return 0;

    size_t price = do_get_blob_price_part_2(map, letter, ps, 0, sides);

    for (Point *it = ps->items; (size_t)(it - ps->items) < ps->length; it++) {
        map.items[it->y][it->x] = '#';
    }

    return price;
}

void map_print(Map map) {
    for (size_t y = 0; y < map.length; y++) {
        for (size_t x = 0; x < map.width; x++) {
            putchar(map.items[y][x]);
        }
        putchar('\n');
    }
}

void side_print(Side *side) {
    switch (side->dir) {
    case NORTH:
        printf("North: ");
        break;
    case WEST:
        printf("West: ");
        break;
    case SOUTH:
        printf("South: ");
        break;
    case EAST:
        printf("East: ");
        break;
    }
    printf("stat = %zu, var = (%zu:%zu)\n", side->stat, side->var_min, side->var_max);
}

void sides_print(Sides sides) {
    if (sides.length == 0) {
        puts("No sides found.");
        return;
    }
    for (Side *it = sides.items; (size_t)(it - sides.items) < sides.length; it++) {
        side_print(it);
    }
}
