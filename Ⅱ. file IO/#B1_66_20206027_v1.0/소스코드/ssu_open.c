// p.68
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
// default header files
#include <stdio.h>
#include <stdlib.h>
// header files for c compiling 

int main(void){
	char *fname = "ssu_test.txt";
	int fd; // file descripter

	// error processing : not necessary but important
	if((fd = open(fname, O_RDONLY)) < 0){ // opne ssu_text.txt in read only 
		fprintf(stderr, "open error for %s\n", fname);
		exit(1); // fail
	}
	else
		printf("Success!\nFilnename : %s\nDescriptor : %d\n", fname, fd); 
		// will be 3 cuz 0(input),1(output),2(error) already allocated
	exit(0); // success
}
