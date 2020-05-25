#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 

int main(int argc, char* argv[])
{
	if(argc != 3){
		fprintf(stderr, "usage : %s <oldname> <newname>\n",argv[0]);
		exit(1);
	}

	// make new link to the same file with argv[1]
	if(link(argv[1], argv[2]) < 0){
	// linkcount == 2
		fprintf(stderr, "link error\n");
		exit(1);
	}
	else
		printf("step1 passed.\n");

	// linkcount == 1 -> real file undeleted yet 
	if(remove(argv[1]) < 0){
		fprintf(stderr, "remove error\n");
		remove(argv[2]);
		// linkcount == 0 & refcount == 0 -> file deleted finally
		exit(1);
	}
	else
		printf("step2 passed.\n");
	// remove only argv[1], so argv[2] pointing the same file still remains.
	
	printf("Success\n");
	exit(0);
}
