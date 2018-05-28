#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

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
	char tmp[64];
	fscanf(f, "%s", tmp);
	printf("%s\n", tmp);

	return 0;
}