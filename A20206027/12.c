#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFFER_SIZE 1024
#define WORD_MAX 100

int main(void)
{
    int fd;
    int length = 0, offset = 0, count = 0;
    char *fname = "ssu_test.txt";
    char buf[WORD_MAX][BUFFER_SIZE];
    int i;
    if ((fd = open(fname, O_RDONLY, 0644)) < 0)
    {
        fprintf(stderr, "read error\n");
        exit(1);
    }

    while (1)
    {
        if ((length = read(fd, buf[count], WORD_MAX)) < 1)
            break;
        printf("%s\n\n", buf[count]);
        for (i = 0; i < length; i++)
        {
            if (buf[count][i] == '\n')
                break;
        }
        offset = lseek(fd, offset + i + 1, SEEK_SET);
        count++;
    }
    printf("line number : %d\n", count);
    exit(0);
}