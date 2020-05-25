#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 4096

int main(void) {
	char buf[MAX_LINE];
	char name[L_tmpnam];
	FILE *fp;

	printf("temp file 1 : %s\n", tmpnam(NULL));
	tmpnam(name); // creat a name for a temporary file

	printf("temp file 2 : %s\n", name);
	if ((fp = tmpfile()) == NULL) { // create a temporary file -> fp
		fprintf(stderr, "tmpfile error\n");	
		exit(1);
	}

	fputs("tmpfile created temporary file.\n", fp); // write to fp
	fseek(fp, 0, SEEK_SET); // set fp postion to the beginning of fp
	if (fgets(buf, sizeof(buf), fp) == NULL) { // read from fp
		fprintf(stderr, "fgets error\n");
		exit(1);	
	}
	fputs(buf, stdout); // print the buf
	exit(0);
}
