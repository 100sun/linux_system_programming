// for monitoring files => modifying?
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

struct stat statbuf;

void ssu_checkfile(char *fname, time_t *time);

int main(int argc, char* argv[])
{
	time_t intertime;
	if(argc != 2){
		fprintf(stderr, "usage: %s <file>\n", argv[0]);
		exit(1);
	}

	// 0 == success, -1 == error
	if((stat(argv[1], &statbuf)) < 0){
		fprintf(stderr, "stat error\n");
		exit(1);
	}
	
	intertime = statbuf.st_mtime;

	while(1){ 
		ssu_checkfile(argv[1], &intertime);
		sleep(10);
	}
}

void ssu_checkfile(char *fname, time_t *time){
	// when file deleted
	if(stat(fname, &statbuf) < 0){
		fprintf(stderr, "Warning : ssu_checkfile() error!\n");
		exit(1);
	}

	else
		// current last modified time != stored last modified time 
		if(statbuf.st_mtime != *time){
			fprintf(stderr, "Warning : %s was modified!.\n", fname);
			// update last modified time	
			*time = statbuf.st_mtime;
		}
}
