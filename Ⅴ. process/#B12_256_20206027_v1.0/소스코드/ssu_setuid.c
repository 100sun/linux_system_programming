#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char* argv[])
{
	char line[256];
	FILE* fp;
	int uid;

	if(argc < 2){
		fprintf(stderr, "usage: %s file_name\n", argv[0]);
		exit(1);
	}

	printf("initially uid = %d and euid = %d\n", getuid(), geteuid()); // get user identify

	// FIRST IMPLEMENT => unauthorized to read => cannot open
	// open 	
	fp = fopen(argv[1], "r"); 
	if(fp == NULL){
		fprintf(stderr, "first open error for %s\n", argv[1]);
		exit(1);
	}
	else{
		printf("first open successful:\n");

		while(fgets(line, 255, fp) != NULL)
			fputs(line, stdout); // print all the contents in the file

		fclose(fp);
	}

	// setuid
	setuid(uid = getuid()); // set user identify 1001 -> 1002
	printf("after setuid(%d):\n uid = %d and euid = %d\n", uid, getuid(), geteuid()); // get user identify
	fp = fopen(argv[1], "r");

	// SECOND IMPLEMENT => SUID set to real UID of itself => fail to open
	// open 	
	if(fp == NULL){
		fprintf(stderr, "second open error for %s\n", argv[1]);
		exit(1);
	}
	else{
		printf("second open successful:\n");

		while(fgets(line, 255, fp) != NULL)
			fputs(line, stdout);// print all the contents in the file
	
		fclose(fp);
	}
    	exit(0);
}
