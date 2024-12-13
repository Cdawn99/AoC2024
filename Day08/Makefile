CFLAGS = -Wall
CFLAGS += -Werror
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -pedantic-errors
CFLAGS += -std=c11
CFLAGS += -ggdb

../build/day8_p1: day8_p1.c day8.c
	$(CC) -o $@ $^ $(CFLAGS)

../build/day8_p2: day8_p2.c day8.c
	$(CC) -o $@ $^ $(CFLAGS)
