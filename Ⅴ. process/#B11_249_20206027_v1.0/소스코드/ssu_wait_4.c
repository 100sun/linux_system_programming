#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    pid_t child1, child2;
    int pid, status;

    if ((child1 = fork()) == 0) // if it is child process
        execlp("date", "date", (char *)0); // status would be negative
    if ((child2 = fork()) == 0)// if it is child process
        execlp("who", "who", (char *)0); // status would be negative
    printf("parent: waiting for children\n");

    while ((pid = wait(&status)) != -1) // wait until there is no child process ( -1 ) 
    {
        if (child1 == pid) // return pid of child process that terminated
            printf("parent: first child: %d\n", (status >> 8)); // exit(0) -> status will be 0
        else if (child2 == pid)// return pid of child process that terminated
            printf("parent: second child: %d\n", (status >> 8)); // exit(0) -> status will be 0
    }
    printf("parent: all children terminated\n");

    exit(0);
}
