default: build run

build:
	gcc -o volume volume.c

run:
	./volume input.wav out.wav 0.1

debug:
	gcc -g -lm -std=c99 -Wall volume.c
	gdb ./a.out 