#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    pid_t pgid;
    pid_t pid;
    if (argc < 2)
    {
        fprintf(stderr, "usage: %s <file>\n", argv[0]);
        exit(1);
    }
    pid = getpid(); // get pid
    pgid = getpgid(atoi(argv[1])); // get process group id  // convert argv[1] to interger
    printf("pid: %d, pgid: %d\n", pid, pgid);
    exit(0);
}
