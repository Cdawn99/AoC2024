// Copyright (c) 2024 Ertan Halilov
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef DAWN_H_
#define DAWN_H_

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DAWN_DEFER_RETURN(ret_val) \
    do {                           \
        result = (ret_val);        \
        goto defer;                \
    } while (0)

/***************
 *Dynamic array*
 ***************/

#define DAWN_DA_FREE(da) free((da).items)

#define DAWN_DA_DEFAULT_CAPACITY 16

#define DAWN_DA_APPEND(da, elem)                                                          \
    do {                                                                                  \
        if ((da)->length == (da)->capacity) {                                             \
            (da)->capacity *= 2;                                                          \
            if ((da)->capacity == 0) {                                                    \
                (da)->capacity = DAWN_DA_DEFAULT_CAPACITY;                                \
            }                                                                             \
            void *dawn_temp = realloc((da)->items, (da)->capacity * sizeof *(da)->items); \
            assert(dawn_temp && "Not enough RAM for realloc");                            \
            (da)->items = dawn_temp;                                                      \
        }                                                                                 \
        (da)->items[(da)->length++] = (elem);                                             \
    } while (0)

#define DAWN_DA_APPEND_MANY(da, elems, elems_count)                                        \
    do {                                                                                   \
        if ((da)->length + elems_count >= (da)->capacity) {                                \
            if ((da)->capacity == 0) {                                                     \
                (da)->capacity = DAWN_DA_DEFAULT_CAPACITY;                                 \
            }                                                                              \
            while ((da)->length + elems_count >= (da)->capacity) {                         \
                (da)->capacity *= 2;                                                       \
            }                                                                              \
            void *dawn_temp = realloc((da)->items, (da)->capacity * sizeof *(da)->items);  \
            assert(dawn_temp && "Not enough RAM for realloc");                             \
            (da)->items = dawn_temp;                                                       \
        }                                                                                  \
        memcpy((da)->items + (da)->length, elems, elems_count * sizeof *(da)->items);      \
        (da)->length += elems_count;                                                       \
    } while (0)

#define DAWN_DA_PREPEND(da, elem)                                                         \
    do {                                                                                  \
        if ((da)->length == (da)->capacity) {                                             \
            (da)->capacity *= 2;                                                          \
            if ((da)->capacity == 0) {                                                    \
                (da)->capacity = DAWN_DA_DEFAULT_CAPACITY;                                \
            }                                                                             \
            void *dawn_temp = realloc((da)->items, (da)->capacity * sizeof *(da)->items); \
            assert(dawn_temp && "Not enough RAM for realloc");                            \
            (da)->items = dawn_temp;                                                      \
        }                                                                                 \
        for (size_t i = (da)->length; i > 0; i--) {                                       \
            (da)->items[i] = (da)->items[i-1];                                            \
        }                                                                                 \
        (da)->items[0] = (elem);                                                          \
        (da)->length++;                                                                   \
    } while (0)

/****************
 *String builder*
 ****************/

typedef struct {
    size_t length;
    size_t capacity;
    char *items;
} DawnStringBuilder;

#define DAWN_SB_FREE(sb) free((sb).items)

#define DAWN_SB_APPEND_CSTR(sb, cstr)    \
    do {                                 \
        const char *s = (cstr);          \
        size_t len = strlen(s);          \
        DAWN_DA_APPEND_MANY(sb, s, len); \
    } while (0)

#define DAWN_SB_APPEND_BUF(sb, buf, bufsize) DAWN_DA_APPEND_MANY(sb, buf, bufsize)

/******************
 *Static functions*
 ******************/

static inline int dawn_mod(int x, int n) {
    return ((x%n) + n) % n;
}

static inline float dawn_rand_float() {
    return (float)rand() / RAND_MAX;
}

/***********
 *Functions*
 ***********/

/**
 * Shift out a command line arg.
 */
char *dawn_shift_args(int *argc, char ***argv);

/**
 * Read the contents of the given file.
 *
 * @param filepath The path to the file to be read.
 * @param content The contents of the file will be appended to this StringBuilder.
 * @return Whether the process was successful.
 *      When a failure occurs, an error message is printed to stderr.
 */
bool dawn_read_entire_file(const char *filepath, DawnStringBuilder *content);

/**
 * Write the content to the given file.
 *
 * @param filepath The path to the file to be written to.
 * @param content The content that is to be written to the file.
 * @return Whether the process was successful.
 *      When a failure occurs, an error message is printed to stderr.
 */
bool dawn_write_entire_file(const char *filepath, const DawnStringBuilder *content);

#endif // DAWN_H_

#ifdef DAWN_IMPLEMENTATION

char *dawn_shift_args(int *argc, char ***argv) {
    assert(*argc > 0);
    char *arg = **argv;
    (*argv)++;
    (*argc)--;
    return arg;
}

bool dawn_read_entire_file(const char *filepath, DawnStringBuilder *content) {
    if (!filepath || !content) return 0;

    bool result;

    FILE *f = NULL;
    char *buf = NULL;

    f = fopen(filepath, "r");
    if (!f) {
        fprintf(stderr, "Failed to open file: %s\n", filepath);
        DAWN_DEFER_RETURN(false);
    }

    if (fseek(f, 0, SEEK_END)) {
        perror("Failed to get to the end of file");
        DAWN_DEFER_RETURN(false);
    }

    long f_size = ftell(f);
    if (f_size < 0) {
        perror("Failed to get the size of the file");
        DAWN_DEFER_RETURN(false);
    }

    if (fseek(f, 0, SEEK_SET)) {
        perror("Failed to get to the start of file");
        DAWN_DEFER_RETURN(false);
    }

    buf = malloc(f_size);
    if (!buf) {
        fprintf(stderr, "Failed to allocate memory for content from %s\n", filepath);
        DAWN_DEFER_RETURN(false);
    }

    size_t read_size = fread(buf, 1, f_size, f);
    if (read_size < (size_t)f_size && ferror(f)) {
        fprintf(stderr, "There was an error while reading %s\n", filepath);
        DAWN_DEFER_RETURN(false);
    }

    DAWN_SB_APPEND_BUF(content, buf, f_size);
    result = true;

defer:
    if (f) fclose(f);
    if (buf) free(buf);
    return result;
}

bool dawn_write_entire_file(const char *filepath, const DawnStringBuilder *content) {
    if (!filepath || !content) return false;

    bool result;

    FILE *f = fopen(filepath, "w+");
    if (!f) {
        perror("Failed to open file!");
        DAWN_DEFER_RETURN(false);
    }

    size_t size = fwrite(content->items, 1, content->length, f);
    if (size < content->length) {
        fprintf(stderr, "ERROR: There was an error when writing content to %s\n", filepath);
        DAWN_DEFER_RETURN(false);
    }

    result = true;

defer:
    if (f) {
        fclose(f);
    }
    return result;
}

#endif // DAWN_IMPLEMENTATION
