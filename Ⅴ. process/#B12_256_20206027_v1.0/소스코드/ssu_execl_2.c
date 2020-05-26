#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    if (fork() == 0) // create a child process to implement "echo"
    {
        execl("/bin/echo", "echo", "this is", "message one", (char *)0); // if it is a child process, then execute that file with the shell command
    	// 수행된 프로세스가 원래 프로세스를 덮어써서 밑의 두 문장이 수행되지 않음
    	fprintf(stderr, "exec error\n");
        exit(1);
    }
    if (fork() == 0) // create a child process to implement "echo"
    {
        execl("/bin/echo", "echo", "this is", "message two", (char *)0);// if it is a child process, then execute that file with the shell command
    	// 수행된 프로세스가 원래 프로세스를 덮어써서 밑의 두 문장이 수행되지 않음
        fprintf(stderr, "exec error\n");
        exit(1);
    }
    if (fork() == 0) // create a child process to implement "echo"
    {
        execl("/bin/echo", "echo", "this is", "message three", (char *)0);// if it is a child process, then execute that file with the shell command
    	// 수행된 프로세스가 원래 프로세스를 덮어써서 밑의 두 문장이 수행되지 않음
        fprintf(stderr, "exec error\n");
        exit(1);
    }
    printf("Parent program ending\n");
    exit(0);
}
