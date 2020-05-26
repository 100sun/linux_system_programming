// making atime/mtime non-changable
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <utime.h> // for utimbuf

int main(int argc, char* argv[])
{
	struct utimbuf time_buf;
	struct stat statbuf;
	int fd;
	int i;

	for(i = 1; i < argc; i++){
		// return actime and modtime values
		if(stat(argv[i], &statbuf) < 0){
			fprintf(stderr, "stat error for %s\n", argv[i]);
			continue;
		}
		if((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0){
			fprintf(stderr, "open error for %s\n", argv[i]);
			continue;
		}

		close(fd);
		time_buf.actime = statbuf.st_atime; // if stat() is not called : changed by open()
		time_buf.modtime = statbuf.st_mtime; // if stat() is not called : changed by rewritng the file 

		if(utime(argv[i], &time_buf) < 0){
			fprintf(stderr, "utime error for %s\n", argv[i]);
			continue;
		}
	}

	exit(0);
}
