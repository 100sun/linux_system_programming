#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char glob_str[] = "write to standard output\n";
int glob_val = 10;

int main(void)
{
	pid_t pid;
	int loc_val;
	loc_val = 100;
	
	if (write(STDOUT_FILENO, glob_str, sizeof(glob_str)-1) != sizeof(glob_str) - 1) { // no buffering
		fprintf(stderr, "write error\n");
		exit(1);
	}
	printf("before fork\n"); 
	// if stdout conncected w/ control terminal => buffering by line (this string remains in buffer)  
	// unless connected 			    => pop the string from the buffer

	if ((pid = fork()) < 0) { // 1. creat a child process and if there is sth in buffer, copy it
		fprintf(stderr, "fork error\n");
		exit(1);
	}
	else if (pid == 0) {
		glob_val++;
		loc_val++;
	}
	else
		sleep(3); // 3. parent process is waiting 
	
	printf("pid = %d, glob_val = %d, loc_val = %d\n", getpid(), glob_val, loc_val);
	exit(0); // 2. exit child process  4. exit parent process(main)
}
