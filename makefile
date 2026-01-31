CFLAGS = -Wall -std=c89
CC = gcc

build: target main.o
	$(CC) -o mcc89 target/main.o

main.o: src/main.c
	$(CC) $(CFLAGS) src/main.c -o target/main.o

target:
	rm -rf target
	mkdir target
