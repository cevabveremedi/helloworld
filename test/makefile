default: build run

build:
	gcc -o test test.c -lm

run:
	./test

clean:
	rm test a.out data.txt

debug:
	gcc -g -lm -std=c99 -w test.c
	gdb ./a.out