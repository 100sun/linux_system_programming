#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char* fname = "ssu_test.txt";
	int fd;

	printf("First printf : Hello, OSLAB!!\n");

	if((fd = open(fname, O_RDONLY)) < 0){ // open file in read mode
		fprintf(stderr, "open error for %s\n", fname);
		exit(1);
	}
	
	if((freopen(fname, "w", stdout)) != NULL) // reopen stdout in write mode to the file
		printf("Second printf : Hello, OSLAB!!\n"); // stdout == printing to the file
		
	exit(0);
}
