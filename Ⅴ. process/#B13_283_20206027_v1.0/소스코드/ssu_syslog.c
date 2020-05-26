#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <syslog.h>
#include <sys/stat.h>
#include <sys/types.h>

int ssu_daemon_init(void);

int main(void)
{
    printf("daemon process initialization\n");

    if (ssu_daemon_init() < 0)
    {
        fprintf(stderr, "ssu_daemon_init failed\n");
        exit(1);
    }

    while (1) // print log messages
    {
        openlog("lpd", LOG_PID, LOG_LPR);
        syslog(LOG_ERR, "open failed lpd %m");
        closelog();
        sleep(5);
    }
    exit(0);
}

int ssu_daemon_init(void)
{
    pid_t pid;
    int fd, maxfd;

    if ((pid = fork()) < 0)
    {
        fprintf(stderr, "fork error\n");
        exit(1);
    }
    else if (pid != 0)
        exit(0); // 1. call fork and have the parent exit

    pid = getpid();
    printf("process %d running as daemon\n", pid);
    setsid();                 // 2. call setsid to create a new session
    signal(SIGTTIN, SIG_IGN); // 3. ignore IO signals of terminal
    signal(SIGTTOU, SIG_IGN); // 3. ignore IO signals of terminal
    signal(SIGTSTP, SIG_IGN); // 3. ignore IO signals of terminal
    maxfd = getdtablesize();

    for (fd = 0; fd < maxfd; fd++)
        close(fd); // 6. unneeded file descriptors should be closed

    umask(0);                       // 4. call umask to set the file mode creation mask to 0
    chdir("/");                     // 5. change the cwd to the root directory
    fd = open("/dev/null", O_RDWR); // 7. connect /dev/null to standard input, output, and error.
    dup(0);                         // 7. connect /dev/null to standard input, output, and error.
    dup(0);                         // 7. connect /dev/null to standard input, output, and error.
    return 0;                       // terminate parent process
}
