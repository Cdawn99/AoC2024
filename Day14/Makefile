CFLAGS = -Wall
CFLAGS += -Werror
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -pedantic-errors
CFLAGS += -std=c11
CFLAGS += -ggdb

../build/day14_p1: day14_p1.c day14.c
	$(CC) -o $@ $^ $(CFLAGS)

../build/day14_p2: day14_p2.c day14.c
	$(CC) -o $@ $^ $(CFLAGS)
