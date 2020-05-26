#include <stdio.h>
#include <stdlib.h>

#define BUFFER_MAX	256

int main(void)
{
	char command[BUFFER_MAX];
	char* prompt = "Prompt>>";
	
	while(1){
		fputs(prompt, stdout); // write the propmt to stdout

		if(fgets(command, sizeof(command), stdin) == NULL) // read in size-1 characters from stdin and stores them into command
			break; // if the command that you read was NULL, break the loop
		
		system(command); // if the command was not NULL, execute the command 
	}

	// first good bye is by system(), second good bye is by original one
	fprintf(stdout, "Good bye...\n");
	fflush(stdout); // discards any buffered data
	
	exit(0);
}
