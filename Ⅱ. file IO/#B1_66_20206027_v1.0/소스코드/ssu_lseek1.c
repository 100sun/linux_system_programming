//p74
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // unix standard header file 
#include <fcntl.h> // for oflag
#include <sys/stat.h> // for mode 
#include <sys/types.h> // for mode_t

int main(void){
	char *fname = "ssu_test.txt";
	off_t fsize; // this declaration means you're gonna use lseek()
	int fd; // file descripter
	
	// error processing
	if((fd = open(fname, O_RDONLY)) < 0) { // open the file in read-only
		fprintf(stderr, "creat error for %s\n", fname);
		exit(1); // fail
	}
	if((fsize = lseek(fd, (off_t)0, SEEK_END)) < 0) { // return offset added 0 to the size of the file
		fprintf(stderr, "lseek error\n");
		exit(1); // fail
	}
	
	printf("The size of <%s> is %ld bytes.\n", fname, fsize);
	
	exit(0); // success
}
