FFLAGS = -Wall
FFLAGS += -Werror
FFLAGS += -Wextra
FFLAGS += -pedantic
FFLAGS += -pedantic-errors
FFLAGS += -std=f2018
FFLAGS += -ggdb

../build/day9_p1: day9.f90 day9_p1.f90
	$(FC) -o $@ $^ $(FFLAGS)

../build/day9_p2: day9.f90 day9_p2.f90
	$(FC) -o $@ $^ $(FFLAGS)
