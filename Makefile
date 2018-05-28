CC = gcc -std=c99 -Wall

.PHONY: clean

hangman: main.o
	$(CC) -o hangman main.o 

main.o: main.c
	$(CC) -c main.c -o main.o

clean:
	rm -rf main main.o