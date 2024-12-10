#ifndef DAY10_H_
#define DAY10_H_

#include "../dawn_utils.h"

#include <stdbool.h>
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

#endif // DAY10_H_
