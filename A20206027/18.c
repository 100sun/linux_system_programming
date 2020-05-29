
// 바. 단, pattern과 일치하는 문자열은 원래 문자열을 출력하지 않고 pattern의 길이만큼의 hole을 생성
// 사. out.txt 파일을 닫음
// 3. ssu_write() 함수는 수정을 금지함
// 4. 프로그램이 정상적으로 수행되었을 시 in.txt파일과 out.txt파일의 크기는 일치할 것
// in.txt 예시
// 18.c
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int ssu_write(int fd, char *buf);
int main()
{
    char buf[128];
    char tmp[2];
    char pattern[4] = "bcd";
    char *pos1 = buf, *pos2 = buf;
    char *fname_in = "in.txt";
    char *fname_out = "out.txt";
    int size, offset = 0;
    int fd1, fd2; //fd1 is input file, fd2 is output file
    int i = 0;

    fd1 = open(fname_in, O_RDONLY);
    fd2 = open(fname_out, O_RDWR | O_CREAT | O_TRUNC);

    // struct stat statbuf;
    // stat(fname_in, &statbuf);
    // size = statbuf.st_size;

    while (1)
    {
        if ((size = read(fd1, buf, 3)) < 3)
        {
            strcpy(buf, " ");
            offset = lseek(fd1, -1, SEEK_CUR);
            read(fd1, buf, 3);
            printf("%s\n", buf);
            ssu_write(fd2, buf);
            break;
        }
        if (!strncmp(buf, pattern, 3))
        {
            lseek(fd2, 3, SEEK_CUR);
            offset = lseek(fd1, -1, SEEK_CUR);
        }
        else
        {
            sprintf(tmp, "%c\0", buf[0]);
            ssu_write(fd2, tmp);
            offset = lseek(fd1, -2, SEEK_CUR);
        }
    }
    close(fd1);
    close(fd2);
    return 0;
}

int ssu_write(int fd, char *buf)
{
    return write(fd, buf, strlen(buf));
}