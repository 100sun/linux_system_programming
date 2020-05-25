#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 

int main(void)
{
	// change the current working directory to /etc
	if(chdir("/etc") < 0){
		fprintf(stderr, "chdir error\n");
		exit(1);
	}
	
	printf("chdir to /etc succeded.\n");
	exit(0);
}
