// file used to generate tests/subjects/general/allchars.php

#include "stdio.h"

int main(int argc, char** argv)
{
	int i, j;
	printf("Single characters:\n");
	for(i = 0; i < 256; i++)
	{
		printf("%d: %c\n", i, (char)i);
	}
	printf("\n");
	printf("\n");


	printf("Double characters:\n");
	for(i = 0; i < 256; i++)
	{
		for(j = 0; j < 256; j++)
		{
			if	(!(
						(i ==  60 && j ==  63)
				))
			{
				printf("%d,%d: %c%c\n", i, j, (char)i, (char)j);
			}
		}
	}
	printf("\n");
	return 0;
}
