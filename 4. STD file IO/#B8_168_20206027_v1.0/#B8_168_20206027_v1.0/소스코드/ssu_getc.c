#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int character;

	while((character = getc(stdin)) != EOF) // get typed(stdin) charcter until the end of line(ctrl D)
		if(putc(character, stdout) == EOF){ // print the character to terminal 
			fprintf(stderr, "standard output error\n"); // error or end of the file
			exit(1);
		}
	
	if(ferror(stdin)){ // to check whether error or end of the file
		fprintf(stderr, "standard input error\n"); 
		exit(1);
	}
	
	exit(0);
}
