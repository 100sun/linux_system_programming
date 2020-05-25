#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE	1024

void ssu_setbuf(FILE* fp, char* buf);

int main(void){
	char buf[BUFFER_SIZE];
	char* fname = "/dev/pts/0"; // opt to the number of terminal 
	FILE* fp;

	if((fp = fopen(fname, "w")) == NULL){
		fprintf(stderr, "fopen error for %s", fname);
 		exit(1);
	}

	// _IOLBF
	ssu_setbuf(fp, buf); // until the line character, put the string(stdout) to the buffer
	fprintf(fp,"Hello, ");
	sleep(1);
	fprintf(fp,"UNIX!!");
	sleep(1);
	fprintf(fp," \n");  // met the line character => fprintf to the terminal and over
	sleep(1);
	// _IONBF  close buf
	setbuf(stdout, NULL); 
	fprintf(fp, "HOW"); // printf to terminal immediately
	sleep(1);
	fprintf(fp, " ARE"); // printf
	sleep(1);
	fprintf(fp, " YOU?"); // print
	sleep(1);
	fprintf(fp, "\n"); // print and over
	sleep(1);

	exit(0);	
}

void ssu_setbuf(FILE* fp, char* buf){
	size_t size;
	int fd;
	int mode;

	fd = fileno(fp);

	if(isatty(fd)) // if fd is a terminal
		mode = _IOLBF;
	else // not a terminal
		mode = _IOFBF;

	if(buf == NULL){
		mode = _IONBF;
		size = 0;
	}
	else 
		size = BUFFER_SIZE; // if not null : size would be set by user

	setvbuf(fp, buf, mode, size);
}
