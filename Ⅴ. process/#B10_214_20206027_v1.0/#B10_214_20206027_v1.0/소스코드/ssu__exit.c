#include <stdio.h>
#include <unistd.h>

int main(void)
{
	printf("Good afternoon?");
	_exit(0); // terminate the calling process immediately (buffer remains)
}
