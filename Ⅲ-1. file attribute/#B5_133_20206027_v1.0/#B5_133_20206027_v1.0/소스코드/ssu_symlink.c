#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 

int main(int argc, char* argv[])
{
	if(argc != 3){
		fprintf(stderr, "usage : %s <actualname> <synname>\n",argv[0]);
		exit(1);
	}

	// creat symbolic link
	if(symlink(argv[1], argv[2]) < 0){
		fprintf(stderr, "symlink error\n");
		exit(1);
	}
	else
		printf("symlink: %s -> %s\n", argv[2], argv[1]);
	
	exit(0);
}
