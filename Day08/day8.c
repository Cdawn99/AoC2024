#include "day8.h"

#include <stdbool.h>
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
    DAWN_DA_FREE(map);
}

size_t map_count_antinodes(Map map) {
    size_t count = 0;
    for (size_t y = 0; y < map.length; y++) {
        for (size_t x = 0; x < map.width; x++) {
            if (map.items[y][x] == '#') count++;
        }
    }
    return count;
}

void mark_antinodes_part_1(Map map, Frequency freq) {
    for (size_t i = 0; i < freq.length - 1; i++) {
        for (size_t j = i + 1; j < freq.length; j++) {
            Point p1 = freq.items[i];
            Point p2 = freq.items[j];
            Point diff = {
                .x = p1.x - p2.x,
                .y = p1.y - p2.y,
            };

            Point candidate1 = {
                .x = p1.x + diff.x,
                .y = p1.y + diff.y,
            };
            Point candidate2 = {
                .x = p2.x - diff.x,
                .y = p2.y - diff.y,
            };

            if (0 <= candidate1.x && (size_t)candidate1.x < map.width && 0 <= candidate1.y && (size_t)candidate1.y < map.length) {
                map.items[candidate1.y][candidate1.x] = '#';
            }
            if (0 <= candidate2.x && (size_t)candidate2.x < map.width && 0 <= candidate2.y && (size_t)candidate2.y < map.length) {
                map.items[candidate2.y][candidate2.x] = '#';
            }
        }
    }
}

void mark_antinodes_part_2(Map map, Frequency freq) {
    for (size_t i = 0; i < freq.length - 1; i++) {
        for (size_t j = i + 1; j < freq.length; j++) {
            Point p1 = freq.items[i];
            Point p2 = freq.items[j];
            Point diff = {
                .x = p1.x - p2.x,
                .y = p1.y - p2.y,
            };

            Point base = p2;
            while (0 <= base.x && (size_t)base.x < map.width && 0 <= base.y && (size_t)base.y < map.length) {
                map.items[base.y][base.x] = '#';
                base.x += diff.x;
                base.y += diff.y;
            }

            base = p2;
            while (0 <= base.x && (size_t)base.x < map.width && 0 <= base.y && (size_t)base.y < map.length) {
                map.items[base.y][base.x] = '#';
                base.x -= diff.x;
                base.y -= diff.y;
            }
        }
    }
}

static void frequenciy_append(Frequencies *freqs, char freq, Point p) {
    size_t f_idx = freqs->length;
    bool found = false;
    for (size_t i = 0; i < freqs->length; i++) {
        if (freqs->items[i].freq == freq) {
            f_idx = i;
            found = true;
            break;
        }
    }
    if (!found) {
        Frequency f = {0};
        f.freq = freq;
        DAWN_DA_APPEND(freqs, f);
    }
    DAWN_DA_APPEND(&freqs->items[f_idx], p);
}

Frequencies frequencies_init(Map map) {
    Frequencies freqs = {0};
    for (size_t y = 0; y < map.length; y++) {
        for (size_t x = 0; x < map.width; x++) {
            if (map.items[y][x] == '.') continue;
            Point p = {.x = x, .y = y};
            frequenciy_append(&freqs, map.items[y][x], p);
            map.items[y][x] = '.';
        }
    }
    return freqs;
}

void frequencies_free(Frequencies freqs) {
    if (freqs.capacity == 0) return;
    for (Frequency *it = freqs.items; (size_t)(it - freqs.items) < freqs.length; it++) {
        DAWN_DA_FREE(*it);
    }
    DAWN_DA_FREE(freqs);
}
