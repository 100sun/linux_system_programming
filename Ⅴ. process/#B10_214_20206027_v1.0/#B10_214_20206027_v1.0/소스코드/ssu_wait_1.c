#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void ssu_echo_exit(int status);

int main(void)
{
    pid_t pid;
    int status;

    // exit(7);
    if ((pid = fork()) < 0)
    {
        fprintf(stderr, "fork error\n");
        exit(1);
    }
    else if (pid == 0)
        exit(7); // normal child process termination => wait(the last 8bits of exit() param)

    if (wait(&status) != pid)
    {
        fprintf(stderr, "wait error\n");
        exit(1);
    }
    ssu_echo_exit(status);

    // abort();
    if ((pid = fork()) < 0)
    {
        fprintf(stderr, "fork error\n");
        exit(1);
    }
    else if (pid == 0)
        abort(); // abnormal child process termination by signal

    if (wait(&status) != pid)
    {

        fprintf(stderr, "wait error\n");
        exit(1);
    }
    ssu_echo_exit(status);

    // status /= 0
    if ((pid = fork()) < 0)
    {
        fprintf(stderr, "fork error\n");
        exit(1);
    }
    else if (pid == 0)
        status /= 0; // abnormal child process termination by signal

    if (wait(&status) != pid)
    {

        fprintf(stderr, "wait error\n");
        exit(1);
    }
    ssu_echo_exit(status);

    exit(0);
}

void ssu_echo_exit(int status)
{
    if (WIFEXITED(status))
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status)); // get the param of exit()
    else if (WIFSIGNALED(status))
        printf("abnormal termination, signal number = %d%s\n", WTERMSIG(status),
#ifdef WCOREDUMP
               WCOREDUMP(status) ? " (core file generated)" : "");
#else
               "");
#endif
    else if (WIFSTOPPED(status))
        printf("child stopped, signal number = %d\n", WSTOPSIG(status));
}
