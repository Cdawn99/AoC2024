#include "day14.h"

#include <ctype.h>

static int64_t parse_int(char *str) {
    int64_t sign = 1;
    if (*str == '-') {
        sign = -1;
        str++;
    }
    int64_t n = 0;
    while (isdigit(*str)) {
        n *= 10;
        n += *str - '0';
        str++;
    }
    return sign * n;
}

RoomSize room_size_init(char *info) {
    int64_t w = parse_int(info);
    while (*info != ',') info++;
    info++;
    int64_t h = parse_int(info);
    return (RoomSize){
        .width = w,
        .height = h,
    };
}

void robot_move(Robot *r, RoomSize size, size_t seconds) {
    r->px += seconds * r->vx;
    r->py += seconds * r->vy;
    r->px = dawn_mod(r->px, size.width);
    r->py = dawn_mod(r->py, size.height);
}

static Robot parse_robot(char *info) {
    Robot r = {0};

    while (!isdigit(*info) && *info != '-') info++;
    r.px = parse_int(info);

    while (*info != ',') info++;
    info++;
    r.py = parse_int(info);

    while (*info != 'v') info++;
    while (!isdigit(*info) && *info != '-') info++;
    r.vx = parse_int(info);

    while (*info != ',') info++;
    info++;
    r.vy = parse_int(info);

    return r;
}

Robots robots_init(DawnStringBuilder info) {
    while (*info.items != 'p') {
        info.items++;
        info.length--;
    }
    Robots rs = {0};
    for (char *it = info.items; (size_t)(it - info.items) < info.length; it++) {
        Robot r = parse_robot(it);
        DAWN_DA_APPEND(&rs, r);
        while (*it != '\0' && *(it + 1) != 'p') it++;
    }
    return rs;
}

void robots_free(Robots rs) {
    DAWN_DA_FREE(rs);
}
