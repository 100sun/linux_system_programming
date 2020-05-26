// get name and size of file in the directory users want
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <dirent.h> // for struct dirent
#include <string.h> // for memcpy()

#define DIRECTORY_SIZE MAXNAMLEN

int main(int argc, char* argv[]) {
	struct dirent *dentry;
	struct stat statbuf;
	char filename[DIRECTORY_SIZE+1];
	DIR* dirp;

	if(argc < 2){
		fprintf(stderr, "usage: %s <directory>\n", argv[0]);
		exit(1);
	}

	// assign the dirp struct 		change directory to access by only the file name (relative path)
	if((dirp = opendir(argv[1]))==NULL || chdir(argv[1])==-1){
		fprintf(stderr, "opendir, chdir error for %s\n", argv[1]);
		exit(1);
	}

	// get a name of the file from dirp
	while((dentry = readdir(dirp)) != NULL){
		if(dentry->d_ino == 0)
			continue;

		// copy block of memory from 2nd param to 1st param 
		memcpy(filename, dentry->d_name, DIRECTORY_SIZE);
		
		if(stat(filename, &statbuf) == -1){
			fprintf(stderr, "stat error for %s\n", filename);
			continue;
		}
	
		// check whether the statbuf is a regular file by using test mecro function	
		if((statbuf.st_mode & S_IFMT) == S_IFREG)
			printf("%-14s %ld\n", filename, statbuf.st_size);
		else
			printf("%-14s\n", filename);
	}	
	exit(0);
}

