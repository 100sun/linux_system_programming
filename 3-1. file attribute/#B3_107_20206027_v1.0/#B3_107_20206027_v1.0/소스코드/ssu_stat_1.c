// check the file info
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	struct stat statbuf;

	if(argc != 2){
		fprintf(stderr, "usage: %s <file>\n", argv[0]);
		exit(1);
	}

	// 0 == success, -1 == error
	if((stat(argv[1], &statbuf)) < 0){
		fprintf(stderr, "stat error\n");
		exit(1);
	}
					    	     // off_t
	printf("%s is %ld bytes\n", argv[1], statbuf.st_size);
	exit(0);
}
