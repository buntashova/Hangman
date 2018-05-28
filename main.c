#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define GAME_MISS 6
#define WORD_FILES_PATH "./words/"
#define MAX_CATEGORIES  4

enum categories {
	animals = 0,
	computers,
	home,
	music
};


int main(void)
{
	int categor = 0;
	char file_name[20] = {0};
	srand(time(NULL));
	categor = (int)(rand()) % MAX_CATEGORIES;
	FILE *f = NULL;
	switch (categor) {
	case animals:
		sprintf(file_name, "%sanimals", WORD_FILES_PATH);
		break;
	case computers:
		sprintf(file_name, "%scomputers", WORD_FILES_PATH);
		break;
	case home:
		sprintf(file_name, "%shome", WORD_FILES_PATH);
		break;
	case music:
		sprintf(file_name, "%smusic", WORD_FILES_PATH);
		break;
	default:
		printf("ERROR!\n");
		break;
	}
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
	char *word = malloc(len * sizeof(char));
	char *hidden = malloc(len * sizeof(char));
	for (int i = 0; i < len; ++i)
	{
		hidden[i] = '*';
	}
	if (word == NULL)
	{
		printf("ERROR\n");
		return -1;
	}
	memcpy(word, tmp, len);
	int cur_miss = 0;
	int leter = 0;
	int hidden_len = 0;
	while (cur_miss < GAME_MISS)
	{
		int flg = 0;
		printf("hidden word [%s]\n", hidden);
		printf("Input leters: ");
		leter = fgetc(stdin);
		fgetc(stdin); // for /n
		printf("%c\n", leter);
		for (int i = 0; i < len; ++i)
		{
			if (word[i] == leter)
			{
				printf("Found\n");
				flg = 1;
				hidden[i] = leter;
				hidden_len++;
				if (hidden_len == len)
				{
					printf("WIN!!!! %s\n", hidden);
					return 0;
				}		
				break;
			}
		}
		if (flg == 0)
		{
			printf("Not found\n");
			cur_miss++;
		}
	}

	return 0;
}