// p75 #include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // unix standard header file 
#include <fcntl.h> // for oflag
#include <sys/stat.h> // for mode 
#include <sys/types.h> // for mode_t

#define CREAT_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) // rw-r--r--

char buf1[] = "1234567890";
char buf2[] = "ABCDEFGHIJ";

int main(void){
	char *fname = "ssu_hole.txt";
	int fd; // file descripter
	
	// error processing
	if((fd = creat(fname, CREAT_MODE)) < 0){ // OPEN in read.write user, read group, read other authorized
		fprintf(stderr, "creat error for %s\n", fname);
		exit(1); // fail
	}

	if(write(fd, buf1, 12) != 12){ // 12 == buffer size, fd = "ssu_hole.txt"'s => write "1234567890" on this file
		fprintf(stderr, "buf1 write error\n");
		exit(1); // fail
	}
	// offset now = 12

	if(lseek(fd, 15000, SEEK_SET) < 0) { // offset : the beginning of the file + 15000bytes  
		fprintf(stderr, "lseek error\n");
		exit(1); // fail
	}
	// offset now = 15000
	
	if(write(fd, buf2, 12) != 12){ // 12 == buffer size, fd = "ssu_hole.txt"'s => write "ABCDEFGHIJ" on this file
		fprintf(stderr, "buf1 write error\n");
		exit(1); // fail
	}
	// offset now = 15012
	
	exit(0); // success
}
