#ifndef __HANGMAN_H__
#define __HANGMAN_H__

#define MAX_MISS 6
#define WORD_FILES_PATH "./words/"
#define MAX_CATEGORIES  4

enum categories {
	animals = 0,
	computers,
	home,
	music
};

int hangman(void);

#endif