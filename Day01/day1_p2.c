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

int str_to_int(char *str) {
    int n = 0;
    while (isdigit(*str)) {
        n *= 10;
        n += *str - '0';
        str++;
    }
    return n;
}

int get_number_count(List l, int n) {
    int count = 0;
    for (size_t i = 0; i < l.length; i++) {
        if (l.items[i] == n) count++;
    }
    return count;
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

    int similarity_score = 0;
    for (size_t i = 0; i < l1.length; i++) {
        int n = l1.items[i];
        int count = get_number_count(l2, n);
        similarity_score += n * count;
    }

    printf("Similarity score: %d\n", similarity_score);

    DAWN_SB_FREE(lists);
    DAWN_DA_FREE(l1);
    DAWN_DA_FREE(l2);

    return 0;
}
