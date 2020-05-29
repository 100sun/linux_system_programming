#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define BUF_MAX 4
int main(int argc, char *argv[])
{
    int fd;               // 읽을 파일 디스크립터
    size_t n;             // read()의 리턴값
    int count = 0;        // 읽은 파일의 라인수
    char buf[2], cbuf[5]; // read()에서 읽는 버퍼와 출력할 버퍼
    if (argc != 2)
    {
        fprintf(stderr, "usage : ./ssu_cat file\n");
        exit(1);
    }
    if ((fd = open(argv[1], O_RDONLY)) < 0)
    {
        fprintf(stderr, "open error");
        exit(1);
    }
    if (write(1, "0 ", 2) < 0)
    {
        fprintf(stderr, "write0 error");
        exit(1);
    }
    while ((n = read(fd, buf, 1)) > 0)
    {
        if (buf[0] == '\n')
        {
            sprintf(cbuf, "\n%d ", ++count);
            if (write(1, cbuf, 4) < 0)
            {
                fprintf(stderr, "write1 error");
                exit(1);
            }
        }
        else
        {
            if (write(1, buf, 1) < 0)
            {
                fprintf(stderr, "write3 error");
                exit(1);
            }
        }
    }
    close(fd);
    exit(0);
}
// - 18 -
// 19. 다음 주어진 ssu_test.txt 파일을 한 줄씩 읽어 줄의 번호와 함께 읽은 줄을 출력하는 프로그램을 작성하시오. (8점)
// < 조 건 >
// 1. 주어진 변수를 그대로 사용할 것, 변수의 추가나 삭제 시 감점
// 1. 각 함수가 정의된 헤더파일을 정확히 쓸 것
// 1. 본 프로그램의 실행파일은 1개의 인자만 받도록 할 것
// 1. open(), read(), close()를 각 1번 씩 사용하고 write()는 3번사용 할 것
// 1. open()함수와 write()함수에 대한 에러 처리를 위해 fprintf() 4번만 사용할 것
// 1. 입력 텍스트 파일이 변경되어도 정상적으로 작동되어야 할 것