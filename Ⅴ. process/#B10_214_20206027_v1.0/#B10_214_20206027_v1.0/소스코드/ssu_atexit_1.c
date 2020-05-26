#include <stdio.h>
#include <stdlib.h>

static void ssu_exit1(void);
static void ssu_exit2(void);

int main(void)
{
	if (atexit(ssu_exit2) != 0) {// order:0
		fprintf(stderr, "atexit error for ssu_exit2");
		exit(1);
	}
	if (atexit(ssu_exit1) != 0) {// order:1
		fprintf(stderr, "atexit error for ssu_exit1");
		exit(1);
	}
	if (atexit(ssu_exit1) != 0) {// order:2
		fprintf(stderr, "atexit error for ssu_exit1");
		exit(1);
	}
	printf("done\n"); // order:4
	exit(0); // order:3
}

static void ssu_exit1(void) {
	printf("ssu_exit1 handler\n");// order:5
}

static void ssu_exit2(void) {
	printf("ssu_exit2 handler\n");// order:6
}
