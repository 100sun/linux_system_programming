//p.94  stdout : printf -> file
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *fname = "ssu_test.txt";
	int count;
	int fd;

	// error processing
	if ((fd = creat(fname, 0666)) < 0)
	{ // rw-rw-rw-
		fprintf(stderr, "open error for %s\n", fname);
		exit(1);
	}

	printf("First printf is on the screen\n");
	int newfd;
	newfd = dup2(fd, 1);								  // 3(created file) -> 1(stdout == printf) => printf -> writing on the created file
	printf("%d\nSecond printf is in this file\n", newfd); // printing on the new file
	exit(0);
}
