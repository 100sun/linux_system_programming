#include <stdio.h>
#include <stdlib.h>

void ssu_out(void);

int main(void)
{
	if (atexit(ssu_out)) { // register ssu_out to be called at normal process termination 
		fprintf(stderr, "atexit error\n");
		exit(1);
	}
	exit(0); // after ssu_out calling
}

void ssu_out(void) { // will be called after main() returned
	printf("atexit succeeded!\n");
}
