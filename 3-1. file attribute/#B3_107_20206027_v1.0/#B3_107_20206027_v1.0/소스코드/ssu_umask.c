// changing mask of files doesn't affect their parent process, shell
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define RW_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

int main(void)
{
	char *fname1 = "ssu_file1";
	char *fname2 = "ssu_file2";

	umask(0);

	// user/group/other : readable, writable => rw-rw-rw-, 0666
	if (creat(fname1, RW_MODE) < 0)
	{
		fprintf(stderr, "creat error for %s\n", fname1);
		exit(1);
	}

	// group/other : readable, writable X => rw-------, 0600
	umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); // == umask(0066)

	// user/group/other : readable, writable => rw-rw-rw-, 0666
	if (creat(fname2, RW_MODE) < 0)
	{
		fprintf(stderr, "creat error for %s\n", fname2);
		exit(1);
	}

	exit(0);
}
