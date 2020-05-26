#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE	1024

int main(void){
	char buf[BUFFER_SIZE];
	// _IOLBF 
	setbuf(stdout, buf); // until the line character, put the string(stdout) to the buffer
	printf("Hello, ");
	sleep(1);
	printf("OSLAB!!");
	sleep(1);
	printf("\n");  // met the line character => print to the terminal and over
	sleep(1);
	// _IONBF  close buf
	setbuf(stdout, NULL); 
	printf("How"); // print to terminal immediately
	sleep(1);
	printf(" are"); // print
	sleep(1);
	printf(" you"); // print
	sleep(1);
	printf("\n"); // print and over
	sleep(1);

	exit(0);	
}
