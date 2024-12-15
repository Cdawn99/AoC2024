CFLAGS = -Wall
CFLAGS += -Werror
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -pedantic-errors
CFLAGS += -std=c11
CFLAGS += -ggdb

../build/day15_p1: day15_p1.c day15.c
	$(CC) -o $@ $^ $(CFLAGS)

../build/day15_p2: day15_p2.c day15.c
	$(CC) -o $@ $^ $(CFLAGS)
