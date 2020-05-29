#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

void print_file_type(struct stat *statbuf)
{
    char *str;
    if (S_ISDIR(statbuf.st_mode))
        printf("directory\n");
    else if (S_ISCHR(statbuf.st_mode))
        printf("character special\n");
    else if (S_ISBLK(statbuf.st_mode))
        printf("block special\n");
    else if (S_ISFIFO(statbuf.st_mode))
        printf("FIFO\n");
    else if (S_ISSBL(statbuf.st_mode))
        printf("symbolic link\n");
    else if (S_ISSOC(statbuf.st_mode))
        printf("socket");
}

int main(int argc, char *argv[])
{
    struct stat statbuf;
    int i;
    for (i = 0; i < argc; i++)
    {
        if (lstat(argv[i], &statbuf) < 0)
        {
            fprintf(sterr, "stat error\n");
            exit(1);
        }
        print_file_type(statbuf);
    }
    exit(0);
}