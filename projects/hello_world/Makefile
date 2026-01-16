CC = gcc
CFLAGS = -c -std=c11 -Wall -Wextra -O2
LD = gcc

all: hello_world

hello_world: main.o
	$(LD) main.o -o hello_world

main.o: main.c
	$(CC) $(CFLAGS) main.c -o main.o

clean:
	rm -f main.o hello_world

help:
	@echo "Makefile for Hello World Project"
	@echo "Targets:"
	@echo "  all      - Compile and link the Hello World program"
	@echo "  clean    - Remove compiled files"
	@echo "  help     - Show this help message"

.PHONY: all clean help
