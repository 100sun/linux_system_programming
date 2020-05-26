#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 

// mode, size -> usually define
#define S_MODE 0644
#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
	char buf[BUFFER_SIZE];
	int fd1, fd2;
	int length;

	// argument error processing
	if(argc != 3){
		fprintf(stderr, "Usage : %s filein fileout\n", argv[0]); // 2 files
		exit(1); 
	}

	// fd1 open for input
	if((fd1 = open(argv[1], O_RDONLY)) < 0){
		fprintf(stderr, "open error for %s\n", argv[1]);
		exit(1);
	} 
	
	// fd2 open for output
	if((fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_MODE)) < 0){ // open argv[2] and creat
		fprintf(stderr, "open error for %s\n", argv[2]);
		exit(1);
	}

	// <copy> read from fd1 and write to fd2  
	while((length = read(fd1, buf, BUFFER_SIZE)) > 0)
		write(fd2, buf, length); 
	
	exit(0);
}
