SHELL := /bin/bash

default: build

build:
	python3 dna.py [] []

test:
	@for i in 1 2 3 4; do \
		python3 dna.py databases/small.csv sequences/$$i.txt; \
		done
	@for i in 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20; do \
		python3 dna.py databases/large.csv sequences/$$i.txt; \
		done

answer:
	@echo Bob
	@echo No match
	@echo No match
	@echo Alice
	@echo Lavender
	@echo Luna
	@echo Ron
	@echo Ginny
	@echo Draco
	@echo Albus
	@echo Hermione
	@echo Lily
	@echo No match
	@echo Severus
	@echo Sirius
	@echo No match
	@echo Harry
	@echo No match
	@echo Fred
	@echo No match

compare:
	diff -y <(make test) <(make answer)