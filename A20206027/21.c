#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

void print_file_type(struct stat *statbuf)
{
    char *str; // 파일의 종류
}
int main(int argc, char *argv[])
{
    struct stat statbuf;
    int i;

    for (i = 0; i < argc; i++)
    {
        if (access(argv[i], F_OK) < 0)
        {
            fprintf(stderr, "access error\n");
            exit(1);
        }
        stat(argv[i], &statbuf);
        if (S_ISREG(statbuf.st_mode))
            printf("regular is %d bytes\n", statbuf.st_size);
        if (S_ISDIR(statbuf.st_mode))
            printf("directory is %d bytes\n", statbuf.st_size);
        if (S_ISCHR(statbuf.st_mode))
            printf("character special is %d bytes\n", statbuf.st_size);
        if (S_ISBLK(statbuf.st_mode))
            printf("block special is %d bytes\n", statbuf.st_size);
        if (S_ISFIFO(statbuf.st_mode))
            printf("FLFO is %d bytes\n", statbuf.st_size);
        if (S_ISLNK(statbuf.st_mode))
            printf("symbolic link is %d bytes\n", statbuf.st_size);
    }
    exit(0);
}