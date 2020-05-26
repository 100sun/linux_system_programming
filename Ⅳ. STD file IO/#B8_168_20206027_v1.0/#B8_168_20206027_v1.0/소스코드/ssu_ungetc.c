#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(void)
{
	char operator;
	FILE* fp;
	int character;
	int number = 0;
	
	if((fp = fopen("ssu_expr.txt", "r")) == NULL){
		fprintf(stderr, "fopen error for ssu_expr.txt\n");
		exit(1);
	}

	while(!feof(fp)){ // until the eof indicator of fp
		while((character = fgetc(fp)) != EOF && isdigit(character)) // EOF X digit O => number
			number = 10 * number + character - 48; // abstract the number 0 (48 in ASCII code)
		
		fprintf(stdout, " %d\n", number);
		number = 0; // reset number
		
		if(character != EOF){ // EOR X digit X => operator
			ungetc(character, fp); // push the chracter back to fp so even you read the character you can re-read it 
			operator = fgetc(fp);
			printf("Operator => %c\n", operator);
		}
	}
	fclose(fp);	
	exit(0);
}
