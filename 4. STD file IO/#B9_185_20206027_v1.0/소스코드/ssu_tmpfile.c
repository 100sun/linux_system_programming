#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(void)
{
	char buf[BUFFER_SIZE];
	char name[L_tmpnam];
	FILE *fp;

	printf("Temporary filename <<%s>>\n", tmpnam(name)); // creat a name for a temporary file
	if ((fp = tmpfile()) == NULL) { // create a temporary file -> fp
		fprintf(stderr, "tmpfile create error!!\n");
		exit(1);
	}

	fputs("create tmpfile success!!\n", fp); // write to fp
	rewind(fp);
	fgets(buf, sizeof(buf), fp); // read from fp
	puts(buf); // write buf to stdout
	
	exit(0);
}
