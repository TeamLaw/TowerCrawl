
#define MAX_LEN 128
#include "TowerCrawl.h"
pullGraphics(char * FileName)
{
	void print_image(FILE *fptr);

	FILE *fptr = NULL;

	if ((fptr = fopen(FileName, "r")) == NULL)
	{
		fprintf(stderr, "error opening %s\n", FileName);
		return 1;
	}

	print_image(fptr);

	fclose(fptr);
}

void print_image(FILE *fptr)
{
	char read_string[MAX_LEN];

	while (fgets(read_string, sizeof(read_string), fptr) != NULL)
		printf("%s", read_string);
}