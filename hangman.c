#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "hangman.h"

char* select_word = NULL;
char* hidden_word = NULL;

char * get_category_file() {
	int category = 0;
	int len = 0;
	char *file_name = NULL;
	char tmp[20] = {0};
	srand(time(NULL));

	category = (int)(rand()) % MAX_CATEGORIES;
	switch (category) {
	case animals:
		sprintf(tmp, "%sanimals", WORD_FILES_PATH);
		printf("\nYour category of game: ANIMALS\n\n");
		break;
	case computers:
		sprintf(tmp, "%scomputers", WORD_FILES_PATH);
		printf("\nYour category of game: COMPUTERS\n\n");
		break;
	case home:
		sprintf(tmp, "%shome", WORD_FILES_PATH);
		printf("\nYour category of game: HOME\n\n");
		break;
	case music:
		sprintf(tmp, "%smusic", WORD_FILES_PATH);
		printf("\nYour category of game: MUSIC\n\n");
		break;
	default:
		printf("Error, can't found category\n");
		break;
	}

	len = strlen(tmp);
	if (len < 0) {
		return NULL;
	}

	file_name = malloc(len * sizeof(char));
	if (!file_name) {
		printf("Error, can't malloc");
		return NULL;
	}
	memset(file_name, 0, len);
	memcpy(file_name, tmp, len);

	return file_name;
}

int get_word(char *file_name) {
	char tmp[32] = {0};
	int count = 0;
	int number_word = 0;
	int word_len = 0;
	FILE *f = NULL;

	if ((f = fopen(file_name, "r")) == NULL) {
		printf("Error, can't open file %s\n", file_name );
		return -1;
	}
	while (fscanf(f, "%*s") != EOF) {
		count++;
	}

	fseek(f, 0, SEEK_SET);
	number_word = (int) rand() % count;
	count = 0;

	while (fscanf(f, "%*s") != EOF) {
		if (count == number_word) {
			break;
		}
		count++;
	}

	fscanf(f, "%s", tmp);

	printf("%s\n", tmp);

	word_len = strlen(tmp);
	select_word = malloc(word_len * sizeof(char));
	hidden_word = malloc(word_len * sizeof(char));

	if (select_word == NULL || hidden_word == NULL) {
		printf("Error, can't malloc\n");
		fclose(f);
		return -1;
	}
	for (int i = 0; i < word_len; ++i) {
		hidden_word[i] = '*';
	}

	memcpy(select_word, tmp, word_len);
	fclose(f);

	return word_len;
}

int is_letter(char ch)
{
	if (('a' <= ch && ch <= 'z')) {
		return 1;
	}
	return 0;
}

int game(int word_len)
{
	int current_miss = 0;
	int letter = 0;
	int hidden_len = 0;
	int found = 0;

	while (current_miss < MAX_MISS) {
		found = 0;
		printf("\nHidden word [%s]\n", hidden_word);
		printf("Input letters: ");
		letter = fgetc(stdin);
		fgetc(stdin); // for /n
		fflush(stdin);

		if (is_letter(letter) == 1) {
			for (int i = 0; i < word_len; ++i) {
				if (select_word[i] == letter && hidden_word[i] != letter) {
					found = 1;
					hidden_word[i] = letter;
					hidden_len++;
					if (hidden_len == word_len) {
						printf("\n[%s] - YOU WIN!\n", hidden_word);
						return 0;
					}
					break;
				}
			}
			if (found == 0) {
				printf("\nLetter - '%c' not found! Try again\n", letter);
				current_miss++;
			}
		}
		else {
			printf("\nINVALID CHARACTER! \nTRY AGAIN \n");
		}
	}
	printf("\nYOU LOSS!\n");

	return 0;
}

int hangman(void)
{
	int word_len = 0;
	char *file_name = NULL;

	file_name = get_category_file();
	if (file_name == NULL) {
		printf("Error, can't get category file");
		return -1;
	}

	word_len = get_word(file_name);
	if (word_len <= 0) {
		printf("Error");
		return -1;
	}

	game(word_len);
	free(file_name);
	free(select_word);
	free(hidden_word);

	return 0;
}