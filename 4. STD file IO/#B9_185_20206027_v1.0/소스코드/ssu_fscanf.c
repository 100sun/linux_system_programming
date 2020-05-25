#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(void)
{
	char *fname = "ssu_test.dat";
	char name[BUFFER_SIZE];
	FILE *fp;
	int age;

	// get the data
	fp = fopen(fname, "r"); // read mode
	fscanf(fp, "%s%d", name, &age); // read input from fp(not stdin)
	fclose(fp);
	// print the data	
	fp = fopen(fname, "w"); // write mode
	fprintf(fp, "%s is %d years old\n", name, age); // write the string to fp
	fclose(fp);
	
	exit(0);
}
