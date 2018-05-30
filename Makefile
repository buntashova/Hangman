CC = gcc -std=c99 -Wall
DEFINE = -DGDK_DISABLE_DEPRECATION_WARNINGS
LIBS = `pkg-config --cflags --libs gtk+-3.0` -rdynamic

.PHONY: clean

bin: hangman.o interface.o main.o 
	$(CC) -o hangman main.o hangman.o interface.o $(LIBS)

main.o: main.c
	$(CC) -c $(DEFINE) main.c -o main.o $(LIBS)

hangman.o: hangman.c
	$(CC) -c $(DEFINE) hangman.c -o hangman.o $(LIBS)

interface.o: interface.c
	$(CC) -c $(DEFINE) interface.c -o interface.o $(LIBS)


clean:
	rm -rf hangman main.o hangman.o interface.o