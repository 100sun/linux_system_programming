// 1. lstat()의 에러 처리를 위해 fprintf()를 1번 사용할 것
// 1. 프로그램 실행 시 프로그램의 인자로 받은 두 파일 중 일반 파일이 아닌 파일이 있으면 fprintf()를 사용하여
// 에러 처리할 것
// 1. 프로그램 실행 시 프로그램의 인자로 받은 두 파일이 모두 일반 파일이라면 system()함수를 사용하여 diff를 실
// 행할 것. 단, diff의 인자의 처리를 위하여 strcpy()를 1번, strcat()를 3번 사용할 것

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
    char buf[BUF_SIZE];
    struct stat statbuf_1, statbuf_2;
    if (argc != 3)
    {
        fprintf(stderr, "usage : %s <filename1> <filename2>\n", argv[0]);
        exit(1);
    }
    if (lstat(argv[1], &statbuf_1))
    {
        fprintf(stderr, "lstat error\n");
        exit(1);
    }
    if (lstat(argv[2], &statbuf_2))
    {
        fprintf(stderr, "lstat error\n");
        exit(1);
    }
    if (S_ISREG(statbuf_1.st_mode) && S_ISREG(statbuf_2.st_mode))
    {
        char command[BUF_SIZE];
        char diff[BUF_SIZE] = "diff ";
        strcpy(command, diff);
        strcat(command, argv[1]);
        strcat(command, " ");
        strcat(command, argv[2]);
        printf("%s\n", command);
        system(command);
    }
    else
    {
        fprintf(stderr, "not a regular file\n");
        exit(1);
    }
    exit(0);
}