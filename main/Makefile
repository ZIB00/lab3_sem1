.PHONY: all

all: queue.o main.o
	gcc -o main queue.o main.o

queue.o: queue.c queue.h
	gcc -c queue.c -o queue.o

main.o: main.c queue.h
	gcc -c main.c -o main.o