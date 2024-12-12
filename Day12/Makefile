CFLAGS = -Wall
CFLAGS += -Werror
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -pedantic-errors
CFLAGS += -std=c11
CFLAGS += -ggdb

../build/day12_p1: day12_p1.c day12.c
	$(CC) -o $@ $^ $(CFLAGS)

../build/day12_p2: day12_p2.c day12.c
	$(CC) -o $@ $^ $(CFLAGS)
