#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "hangman.h"
#include "interface.h"

char* select_word = NULL;
char* hidden_word = NULL;
char* category_str = NULL;
int word_len = 0;
int hidden_len = 0;
int current_miss = 0;

void set_category_str(char *str)
{
	int len = strlen(str);
	category_str = malloc(len + 1);
	memset(category_str, 0, len + 1);
	strcat(category_str, str);
}

char * get_category_file()
{
	int category = 0;
	int len = 0;
	char *file_name = NULL;
	char tmp[20] = {0};
	srand(time(NULL));

	category = (int)(rand()) % MAX_CATEGORIES;
	switch (category) {
	case animals:
		sprintf(tmp, "%sanimals", WORD_FILES_PATH);
		set_category_str("animals");
		printf("\nYour category of game: ANIMALS\n\n");
		break;
	case computers:
		sprintf(tmp, "%scomputers", WORD_FILES_PATH);
		printf("\nYour category of game: COMPUTERS\n\n");
		set_category_str("computers");
	case home:
		sprintf(tmp, "%shome", WORD_FILES_PATH);
		printf("\nYour category of game: HOME\n\n");
		set_category_str("home");
		break;
	case music:
		sprintf(tmp, "%smusic", WORD_FILES_PATH);
		printf("\nYour category of game: MUSIC\n\n");
		set_category_str("music");
		break;
	default:
		printf("Error, can't found category\n");
		break;
	}

	len = strlen(tmp);
	if (len < 0) {
		return NULL;
	}

	file_name = malloc(len * sizeof(char) + 1);
	if (!file_name) {
		printf("Error, can't malloc");
		return NULL;
	}
	memset(file_name, 0, len + 1);
	memcpy(file_name, tmp, len);

	return file_name;
}

int get_word(char *file_name)
{
	char tmp[32] = {0};
	int count = 0;
	int number_word = 0;
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
	word_len = strlen(tmp);
	if (word_len <= 0) {
		return -1;
	}
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
	memcpy(select_word, tmp, word_len);
	printf("Word: %s\n", select_word);
	fclose(f);

	return 1;
}

int is_letter(char ch)
{
	if (('a' <= ch && ch <= 'z')) {
		return 1;
	}
	return 0;
}


void game()
{
	char letter = 0;
	int found = 0;
	char pic[10] = {0};

	const char *text = gtk_entry_get_text(textBox);
	letter = text[0];
	gtk_entry_set_text(textBox, "");
	gtk_label_set_text(Label_category, category_str);

	if (is_letter(letter) == 1) {
		for (int i = 0; i < word_len; ++i) {
			if (select_word[i] == letter && hidden_word[i] != letter) {
				found = 1;
				hidden_word[i] = letter;
				hidden_len++;
				if (hidden_len == word_len) {
					gtk_widget_hide(gameWindow);
					gtk_widget_show(msgWindow);
					gtk_label_set_text(Label_word, select_word);

					gtk_label_set_text(gameMsg, "You Win!");
					printf("\n[%s] - YOU WIN!\n", hidden_word);
					return;
				}
				break;
			}
		}

		if (found == 0) {
			current_miss++;
			sprintf(pic, "pic/%d.jpg", current_miss + 1);
			gtk_image_set_from_file(hangmanImage, pic);
			printf("\nLetter - '%c' not found! Try again\n", letter);
		}
	} else {
		printf("\nINVALID CHARACTER! \nTRY AGAIN \n");
	}
	if (current_miss == MAX_MISS) {
		gtk_widget_hide(gameWindow);
		gtk_widget_show(msgWindow);
		gtk_label_set_text(Label_word, select_word);
		sprintf(pic, "pic/%d.jpg", current_miss + 1);
		gtk_image_set_from_file(msgImage, pic);
		gtk_label_set_text(gameMsg, "You Loss!");
		printf("\nYOU LOSS!\n");
		return;
	}
	gtk_label_set_text(Label_hidden, hidden_word);

	printf("\nHidden word [%s]\n", hidden_word);

	return;
}


void hangman(void)
{
	char *file_name = NULL;
	int ret = 0;
	gtk_image_set_from_file(hangmanImage, "pic/1.jpg");
	gtk_widget_hide(startWindow);
	gtk_widget_hide(msgWindow);
	gtk_widget_show(gameWindow);
	file_name = get_category_file();
	if (file_name == NULL) {
		printf("Error, can't get category file");
		exit(1);
	}

	ret = get_word(file_name);
	if (ret <= 0) {
		printf("Error");
		exit(1);
	}
	current_miss = 0;
	hidden_len = 0;
	gtk_label_set_text(Label_category, category_str);
	gtk_label_set_text(Label_hidden, hidden_word);

	return;
}