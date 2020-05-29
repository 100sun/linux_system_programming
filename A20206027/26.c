// 각 함수가 정의된 헤더파일을 정확히 쓸 것
// 1. getc(), putc(), getchar(), putchar(), fgets(), fputs(), scanf(), printf()를 각 1번씩 사용할 것
// 1. 입·출력 함수의 에러처리를 위해 fprintf()를 3번 사용할 것
// 1. 각 주석에 해당하는 입·출력 함수를 사용할 것
// 1. 파일 타입은 주어진 print_file_type()를 통해 실행결과와 같이 출력할 것
// 1. 실행결과와 같이 문자열을 출력할 것

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define BUFFER_SIZE 1024
int main(void)
{
    char character;
    char buf[BUFFER_SIZE];
    //getchar(), putchar() 사용
    while ((character = getchar()) != EOF)
    {
        putchar(character);
    }
    //getc(), putc() 사용
    printf("2\n");
    while ((character = getc(stdin)) != EOF)
    {
        if (ferror(stdin))
        {
            fprintf(stderr, "standard input error\n");
            exit(1);
        }
        putc(character, stdout);
    }
    printf("3\n");
    //fgets(), fputs() 사용
    while (fgets(buf, BUFFER_SIZE, stdin) != NULL)
    {
        if (ferror(stdin))
        {
            fprintf(stderr, "standard input error\n");
            exit(1);
        }
        fputs(buf, stdout);
        if (buf == EOF)
            break;
    }
    memset(buf, 0, sizeof(buf));
    //scanf(), printf() 사용
    printf("4\n");
    scanf("%[^\n]s", &buf);
    printf("%s", buf);
    exit(0);
}