C:=gcc -Wall -Wextra -O0 -Og -std=gnu23

fc:=$(shell pkg-config --cflags cairo)
fp:=$(shell pkg-config --cflags pango)
fpc:=$(shell pkg-config --cflags pangocairo)

lc:=$(shell pkg-config --libs cairo)
lp:=$(shell pkg-config --libs pango)
lpc:=$(shell pkg-config --libs pangocairo)

main.out: main.o
	$(C) -o $@ $^ $(lp) $(lc) $(lpc)
	@echo

main.o: main.c
	$(C) -c $(fp) $(fc) $(fpc) -o $@ $^
	@echo
