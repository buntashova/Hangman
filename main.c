#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define GAME_MISS 6
#define WORD_FILES_PATH "./words/"
#define MAX_CATEGORIES  4

char* select_word = NULL;
char* hidden_word = NULL;

enum categories {
	animals = 0,
	computers,
	home,
	music
};

char * select_categorie() {
	int categor = 0;
	char tmp[20] = {0};
	srand(time(NULL));
	categor = (int)(rand()) % MAX_CATEGORIES;
	switch (categor) {
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
		printf("ERROR!\n");
		break;
	}
	int len = strlen(tmp);
	if (len < 0)
	{
		return NULL;
	}
	char *file_name = malloc(len * sizeof(char));
	if (!file_name) {
		printf("ERROR malloc");
		return NULL;
	}
	memset(file_name, 0, len);
	memcpy(file_name, tmp, len);
	return file_name;
}

int get_word(char *file_name) {
	FILE *f = NULL;
	if ( ( f = fopen( file_name, "r" ) ) == NULL ) {
		printf( "Can not open file %s\n", file_name );
		return -1;
	}
	int count = 0;
	while ( fscanf( f, "%*s" ) != EOF ) {
		count++;
	}
	fseek ( f , 0 , SEEK_SET );
	int num_word = (int) rand() % count;
	count = 0;
	while ( fscanf( f, "%*s" ) != EOF ) {
		if (count == num_word)
		{
			break;
		}
		count++;
	}
	char tmp[32] = {0};
	fscanf(f, "%s", tmp);
	printf("%s\n", tmp);
	int len = strlen(tmp);
	select_word = malloc(len * sizeof(char));
	hidden_word = malloc(len * sizeof(char));
	if (select_word == NULL || hidden_word == NULL)
	{
		printf("ERROR malloc\n");
		fclose(f);
		return -1;
	}
	for (int i = 0; i < len; ++i)
	{
		hidden_word[i] = '*';
	}
	memcpy(select_word, tmp, len);
	fclose(f);
	return len;
}

int check_letter(char ch)
{
	if (('a' <= ch && ch <= 'z'))
	{
		return 1;
	}
	return 0;
}

int game(int word_len)
{
	int cur_miss = 0;
	int leter = 0;
	int hidden_len = 0;
	while (cur_miss < GAME_MISS)
	{
		int flg = 0;
		printf("\nHidden word [%s]\n", hidden_word);
		printf("Input leters: ");
		leter = fgetc(stdin);
		fgetc(stdin); // for /n
		fflush(stdin);
		if (check_letter(leter) == 1)
		{
			for (int i = 0; i < word_len; ++i)
			{
				if (select_word[i] == leter && hidden_word[i] != leter)
				{

					flg = 1;
					hidden_word[i] = leter;
					hidden_len++;
					if (hidden_len == word_len)
					{
						printf("\nYOU WIN!!!! %s\n", hidden_word);
						return 0;
					}
					break;
				}
			}
			if (flg == 0)
			{
				printf("\nLetter - '%c' not found! Try again\n", leter);
				cur_miss++;
			}
		}
		else {
			printf("\nINVALID CHARACTER! \nTRY AGAIN \n");
		}
	}
	printf("\nYOU LOSS\n");
	return 0;
}

int main(void)
{


	char *file_name = NULL;
	file_name = select_categorie();
	if (file_name == NULL)
	{
		printf("ERROR");
		return -1;
	}
	int len = get_word(file_name);
	if (len < 0)
	{
		printf("Error");
		return -1;
	}
	game(len);
	free(file_name);
	free(select_word);
	free(hidden_word);
	return 0;
}