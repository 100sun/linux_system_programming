#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE	1024

int main(void)
{
	char buf[BUFFER_SIZE];
	
	while(fgets(buf, BUFFER_SIZE, stdin) != NULL) // read in size-1 chracters from stdin and stores them into buf
		if(fputs(buf, stdout) == EOF){ // write the buf to stdout
			fprintf(stderr, "standart output error\n");
			exit(1);
		}
	
	if(ferror(stdin)){
		fprintf(stderr, "standart input error\n");
		exit(1);
	}

	exit(0);
}
