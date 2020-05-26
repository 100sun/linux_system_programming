#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE	1024

int main(int argc, char* argv[])
{
	char buf[BUFFER_SIZE];
	FILE* fp;

	if(argc != 2){
		fprintf(stderr, "usage :%s <file>\n", argv[0]);
		exit(1);
	}

	if((fp = fopen(argv[1], "w+")) == NULL){ // if it doesn't exist, not NULL, just create
		fprintf(stderr, "fopen error for %s\n", argv[1]);
		exit(1);
	}

	fputs("Input String >> ", stdout); 

	gets(buf); // read a line and then place with NULL character
	fputs(buf, fp); // write buf to fp without NULL character
	
	rewind(fp); 
	fgets(buf, sizeof(buf), fp); // read from fp and store them into buf
	
	puts(buf); // write the string of buf to stdout
	
	fclose(fp);
	exit(0);
}
