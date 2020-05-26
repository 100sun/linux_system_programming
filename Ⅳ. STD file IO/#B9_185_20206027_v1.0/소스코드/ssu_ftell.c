#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *fname = "ssu_test.txt";
	FILE *fp;
	long fsize;

	if ((fp = fopen(fname, "r")) == NULL) { // open it in read mode
		fprintf(stderr, "fopen error for %s\n", fname);
		exit(1);
	}
	
	fseek(fp, 0, SEEK_END); // set fp postion to the end of file
	fsize = ftell(fp); // obtain the current value of fp position == the size of file ( cuz it was 0, seek_end )
	printf("The size of <%s> is %ld bytes\n", fname, fsize);

	exit(0);
}
