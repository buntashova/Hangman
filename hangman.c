#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "hangman.h"
#include "interface.h"

char* select_word = NULL;
char* hidden_word = NULL;
int word_len = 0;
char* category_str = NULL;
int hidden_len = 0;


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
		len = strlen("animals");
		category_str = malloc(len + 1);
		memset(category_str, 0, len + 1);
		strcat(category_str, "animals");
		printf("\nYour category of game: ANIMALS\n\n");
		break;
	case computers:
		sprintf(tmp, "%scomputers", WORD_FILES_PATH);
		printf("\nYour category of game: COMPUTERS\n\n");
		len = strlen("computers");
		category_str = malloc(len + 1);
		memset(category_str, 0, len + 1);
		strcat(category_str, "computers");break;
	case home:
		sprintf(tmp, "%shome", WORD_FILES_PATH);
		printf("\nYour category of game: HOME\n\n");
		len = strlen("home");
		category_str = malloc(len + 1);
		memset(category_str, 0, len + 1);
		strcat(category_str, "home");
		break;
	case music:
		sprintf(tmp, "%smusic", WORD_FILES_PATH);
		printf("\nYour category of game: MUSIC\n\n");
		len = strlen("music");
		category_str = malloc(len + 1);
		memset(category_str, 0, len + 1);
		strcat(category_str, "music");
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
	if (word_len <= 0)
		return -1;
	select_word = malloc(word_len * sizeof(char) + 1);
	hidden_word = malloc(word_len * sizeof(char) + 1);
	memset(select_word, 0, word_len + 1);
	memset(hidden_word, 0, word_len + 1);
	if (select_word == NULL || hidden_word == NULL) {
		printf("Error, can't malloc\n");
		fclose(f);
		return -1;
	}
	for (int i = 0; i < word_len; ++i) {
		hidden_word[i] = '*';
	}
	printf("Word: %s\n", select_word);
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

int current_miss = 0;

void game()
{
	gtk_label_set_text(gameLabel2, category_str);

	// gtk_image_set_from_file(hangmanImage, "pic/1.jpg");
	// gtk_widget_hide(startWindow);
	// gtk_widget_hide(msgWindow);
	// gtk_widget_show(gameWindow);
	char letter = 0;
	int found = 0;

	const char *text = gtk_entry_get_text(textBox);
	letter = text[0];
	gtk_entry_set_text(textBox, "");
	found = 0;
	if (is_letter(letter) == 1) {
		for (int i = 0; i < word_len; ++i) {
			if (select_word[i] == letter && hidden_word[i] != letter) {
				found = 1;
				hidden_word[i] = letter;
				printf("\n%c ", hidden_word[i]);

				hidden_len++;
				if (hidden_len == word_len) {
					printf("\n[%s] - YOU WIN!\n", hidden_word);
					return;
				}
				break;
			}
		}
		if (found == 0) {
			char pic[10] = {0};
			current_miss++;
			sprintf(pic, "pic/%d.jpg",current_miss+1);
			printf("pic %s\n", pic);
			gtk_image_set_from_file(hangmanImage, pic);
    		// gtk_widget_show(gameWindow);

			printf("\nLetter - '%c' not found! Try again\n", letter);
		}
	}
	else {
		printf("\nINVALID CHARACTER! \nTRY AGAIN \n");
	}
	gtk_label_set_text(gameLabel3, hidden_word);

	if (current_miss == MAX_MISS)
		printf("\nYOU LOSS!\n");

	printf("\nHidden word [%s]\n", hidden_word);

	return;
}

void hangman(void)
{
	char *file_name = NULL;
	gtk_image_set_from_file(hangmanImage, "pic/1.jpg");
	gtk_widget_hide(startWindow);
	// gtk_widget_hide(msgWindow);
	gtk_widget_show(gameWindow);
	file_name = get_category_file();
	if (file_name == NULL) {
		printf("Error, can't get category file");
		return;
	}

	word_len = get_word(file_name);
	if (word_len <= 0) {
		printf("Error");
		return;
	}

	gtk_label_set_text(gameLabel2, category_str);
	gtk_label_set_text(gameLabel3, hidden_word);
	// game(word_len);
	// free(file_name);
	// free(select_word);
	// free(hidden_word);

	return;
}