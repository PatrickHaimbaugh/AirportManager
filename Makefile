flags= -std=c99 -g -Wall
CC= gcc
src= airport_manager.c
Target=airport_manager

all:$(src)
	$(CC) $(flags) -o $(Target) $(src) -lm

clean:
	rm $(Target) *.out total.txt
