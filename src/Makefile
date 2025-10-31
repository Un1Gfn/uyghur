C:=gcc -Wall -Wextra -O0 -Og -std=gnu23

fc:=$(shell pkg-config --cflags cairo)
fp:=$(shell pkg-config --cflags pango)
fpc:=$(shell pkg-config --cflags pangocairo)

lc:=$(shell pkg-config --libs cairo)
lp:=$(shell pkg-config --libs pango)
lpc:=$(shell pkg-config --libs pangocairo)

P:=/home/darren/Desktop/ugpc.pdf

$P: my.out
	./my.out

%.out: %.o
	$(C) -o $@ $^ $(lp) $(lc) $(lpc)
	@echo

%.o: %.c
	$(C) -c $(fp) $(fc) $(fpc) -o $@ $^
	@echo

vim:
	exec vim -p *.c Makefile

okular: $P
	exec okular $P >/dev/null 2>/dev/null

.PHONY: vim default
.PRECIOUS: %.o

