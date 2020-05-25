#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 

#define PATH_MAX	1024

int main(void)
{
	char* pathname;

	// change the current working directory 
	if(chdir("/home/oslab") < 0){
		fprintf(stderr, "chdir error\n");
		exit(1);
	}

	pathname = malloc(PATH_MAX);

	// check the current working directory (return it)
	if(getcwd(pathname, PATH_MAX) == NULL){
		fprintf(stderr, "getcwd error\n");
		exit(1);
	}

	printf("current directory = %s\n", pathname);
	exit(0);
}
