//p.95 stdout : printf -> write
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(void)
{
	char buf[BUFFER_SIZE];
	char *fname = "ssu_test.txt"; int count;
	int fd;
	int length;

	// error processing
	if((fd = open(fname, O_RDONLY, 0644)) < 0){ // rw-r--r-- only user can write
	       	fprintf(stderr, "open error for %s\n", fname);
		exit(1);
	}

	if(dup2(1, 4) != 4){ // 1(stdout) -> 4 / dup -> 3
		fprintf(stderr, "dup2 call failed\n");
		exit(1);
	}

	while(1){
		length = read(fd, buf, BUFFER_SIZE); // until length == size of the buf

		if(length <= 0) break;

		write(4, buf, length); // write buf in the size of length in file descripter 4 you duplicated
	}

	exit(0);
}
