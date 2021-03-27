#speller:
#	clang -ggdb3 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -c -o speller.o speller.c
#	clang -ggdb3 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -c -o dictionary.o dictionary.c
#	clang -ggdb3 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -o speller speller.o dictionary.o -lm

#CC = mansfield.txt
#CC = bible.txt
#CC = koran.txt
CC = tolstoy.txt 
#CC = lalaland.txt 
#CC = shakespeare.txt

default: build run

build:
	gcc -o speller speller.c dictionary.c -lm -Wall

clean:
	rm speller.o dictionary.o speller a.out result.txt

run:
	./speller texts/$(CC)

check:
	./speller texts/$(CC) > result.txt
	diff -y result.txt keys/$(CC)

debug:
	gcc -g -lm -std=c99 -Wall speller.c dictionary.c
	gdb ./a.out 