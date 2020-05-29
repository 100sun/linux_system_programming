#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE 128
int main(int argc, char *argv[])
{
    char buf[BUFFER_SIZE];
    int fd1, fd2;
    ssize_t size;
    if (argc != 3)
    {
        fprintf(stderr, "usage:[][]");
        exit(1);
    }
    if ((fd1 = open(argv[1], O_RDONLY)) < 0)
    {
        fprintf(stderr, "open error");
        exit(1);
    }
    int length = read(fd1, buf, BUFFER_SIZE * 2);
    close(fd1);

    if ((fd2 = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) < 0)
    {
        fprintf(stderr, "open error");
        exit(1);
    }
    write(fd2, buf, length);
    close(fd2);

    exit(0);
}