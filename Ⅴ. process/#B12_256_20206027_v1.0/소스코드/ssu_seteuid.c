#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(void)
{
    int fd, state;
    state = seteuid(1000); // uid : 0 -> uid : 1001(real user id) => ssu_text.txt's owner will become sun
    if (state < 0) // seteuid error 
    {
        fprintf(stderr, "seteuid error\n");
        exit(1);
    }
    if ((fd = open("ssu_test.txt", O_CREAT | O_RDWR, S_IRWXU)) < 0) // create as root
    {
        fprintf(stderr, "open error\n");
        exit(1);
    }
    close(fd);
    exit(0);
}
