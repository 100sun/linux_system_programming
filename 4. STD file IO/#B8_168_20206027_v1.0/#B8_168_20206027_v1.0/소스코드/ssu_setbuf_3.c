#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE	1024

int main(void){
	char buf[BUFFER_SIZE];
	int a, b;
	int i;

	// _IOLBF 
	setbuf(stdin, buf); // until the line character, put the string(typed by user) to the buffer
	scanf("%d %d", &a, &b);

	for(i = 0; buf[i] != '\n'; i++) // if enter : stop pushing 
		putchar(buf[i]);
	
	putchar('\n'); // print the buffer
	exit(0);
}
