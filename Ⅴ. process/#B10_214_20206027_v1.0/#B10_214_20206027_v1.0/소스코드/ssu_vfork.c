#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

void ssu_local_func(void);

int main(void)
{
    printf("Before vfork\n");
    ssu_local_func(); // vfork()
    printf("After ssu_local_func, my PID is %d\n", getpid());
    exit(0);
}

void ssu_local_func(void)
{
    pid_t pid;
    if ((pid = vfork()) == 0) // create a child process and block parent
        printf("I'm child. My PID is %d\n", getpid()); // if child process
    else if (pid > 0)
        sleep(3); // if parent process
    else
        fprintf(stderr, "vfork error\n"); // if error
}
