CFLAGS = -Wall
CFLAGS += -Werror
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -pedantic-errors
CFLAGS += -std=c11
CFLAGS += -ggdb

../build/day10_p1: day10_p1.c day10.c
	$(CC) -o $@ $^ $(CFLAGS)

../build/day10_p2: day10_p2.c day10.c
	$(CC) -o $@ $^ $(CFLAGS)
