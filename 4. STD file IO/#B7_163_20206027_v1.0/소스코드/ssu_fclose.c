#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char* fname = "ssu_test.txt";
	FILE* fp;

	if((fp = open(fname, "r")) == NULL){ // open file in read mode
		fprintf(stderr, "fopen error for %s\n", fname);
		exit(1);
	}
	else{
		printf("Success!\n");
		printf("Opening \ \"%s\" in \"r\" mode!\n", fname);
	}
		
	fclose(fp); // close opened file	
	exit(0);
}
