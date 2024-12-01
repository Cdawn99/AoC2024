#define DAWN_IMPLEMENTATION
#include "../dawn_utils.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t length;
    size_t capacity;
    int *items;
} List;

int ord_list_diff(List l1, List l2) {
    assert(l1.length == l2.length && "Lists must have the same length");

    int diff = 0;
    for (size_t i = 0; i < l1.length; i++) {
        diff += abs(l1.items[i] - l2.items[i]);
    }
    return diff;
}

int str_to_int(char *str) {
    int n = 0;
    while (isdigit(*str)) {
        n *= 10;
        n += *str - '0';
        str++;
    }
    return n;
}

int compare_ints(const void *v1, const void *v2) {
    int i1 = *(int*)v1;
    int i2 = *(int*)v2;

    if (i1 < i2) {
        return -1;
    }
    if (i1 > i2) {
        return 1;
    }
    return 0;
}

int main(int argc, char **argv) {
    char *program = dawn_shift_args(&argc, &argv);
    if (argc == 0) {
        printf("Usage: %s <list_pairs.txt>\n", program);
        return 1;
    }

    char *lists_path = dawn_shift_args(&argc, &argv);

    DawnStringBuilder lists = {0};
    if (!dawn_read_entire_file(lists_path, &lists)) {
        return 1;
    }
    DAWN_SB_APPEND_BUF(&lists, "", 1);

    List l1 = {0};
    List l2 = {0};

    char delim[] = " \n";
    char *token = strtok(lists.items, delim);
    while (token) {
        int n1 = str_to_int(token);
        DAWN_DA_APPEND(&l1, n1);
        token = strtok(NULL, delim);

        int n2 = str_to_int(token);
        DAWN_DA_APPEND(&l2, n2);
        token = strtok(NULL, delim);
    }

    qsort(l1.items, l1.length, sizeof(*l1.items), compare_ints);
    qsort(l2.items, l2.length, sizeof(*l2.items), compare_ints);

    int diff = ord_list_diff(l1, l2);
    printf("Total distance: %d\n", diff);

    DAWN_SB_FREE(lists);
    DAWN_DA_FREE(l1);
    DAWN_DA_FREE(l2);

    return 0;
}
