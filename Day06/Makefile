CFLAGS = -Wall
CFLAGS += -Werror
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -pedantic-errors
CFLAGS += -std=c11
CFLAGS += -ggdb

../build/day6_p1: day6_p1.c day6.c
	$(CC) -o $@ $^ $(CFLAGS)

../build/day6_p2: day6_p2.c day6.c
	$(CC) -o $@ $^ $(CFLAGS)
