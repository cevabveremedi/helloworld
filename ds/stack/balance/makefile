default: build run

build:
	gcc -o check check.c

run:
	./check

debug:
	gcc -g -lm -std=c99 -Wall check.c
	gdb ./a.out 