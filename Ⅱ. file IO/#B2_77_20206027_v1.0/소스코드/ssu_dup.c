//p.93 open -> dup => same file
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
	int fd1, fd2;

	// error processing
	if((fd1 = open(fname, 0644)) < 0){ // rw-r--r-- only user can write
		fprintf(stderr, "open error for %s\n", fname);
		exit(1);
	}
	fd2 = dup(fd1); // fd2 : the unused lowest fd

	count = read(fd1, buf, 12);
	buf[count] = 0; // for processing null charcter 
	printf("fd1's printf : %s\n", buf);
	
	lseek(fd1, 1, SEEK_CUR); // for processing space (offset = current offset + 1)
        // fd1, fd2 share same ft -> share same offset and same file descripter with ssu_text.txt file 
	
	count = read(fd2, buf, 12);
	buf[count] = 0;
	printf("fd2's printf : %s\n", buf);
	
	exit(0);
}
