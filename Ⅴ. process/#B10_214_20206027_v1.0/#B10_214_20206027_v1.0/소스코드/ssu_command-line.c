#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int i;
	for (i = 0; i < argc; i++) // argc : the number of arguments
		printf("argv[%d] : %s\n", i, argv[i]); // argv[] : string type arguents
	exit(0);
}
