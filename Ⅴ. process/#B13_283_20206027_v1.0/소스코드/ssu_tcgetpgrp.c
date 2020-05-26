#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <signal.h>
#include <termios.h>

#define STDIN_NUMBER 0

static void ssu_sig_hup(int signum);
static void ssu_print_ids(char *name);

int main(void)
{
    pid_t pid;
    char character;

    ssu_print_ids("parents");
    if ((pid = fork()) < 0) // error
    {
        fprintf(stderr, "fork error\n");
    }
    else if (pid > 0) // parent process
    {
        sleep(3);
        exit(0);
    }
    else // ==0 , child process
    { 
        ssu_print_ids("child");
        signal(SIGHUP, ssu_sig_hup);
        kill(getpid(), SIGTSTP);
        ssu_print_ids("child");

        if(read(STDIN_FILENO, &character, 1)!=1)
            fprintf(stderr, "read error\n");
        
        exit(0);
    }
}

static void ssu_sig_hup(int signum){
    printf("ssu_SIG_HUP received, pid = %d\n", getpid());
    }

static void ssu_print_ids(char *name){
    printf("[%s] : pid = %d, ppid = %d, pgrp = %d, tgrp = %d\n", name, getpid(), getppid(), getpgrp(), tcgetpgrp(STDIN_NUMBER));
    fflush(stdout);
}
