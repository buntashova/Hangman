CC = gcc -std=c99 -Wall

.PHONY: clean

bin: main.o hangman.o
	$(CC) -o hangman main.o hangman.o

main.o: main.c
	$(CC) -c main.c -o main.o

hangman.o: hangman.c
	$(CC) -c hangman.c -o hangman.o

clean:
	rm -rf hangman main.o hangman.o