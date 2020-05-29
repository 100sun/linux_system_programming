#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifdef PATH_MAX
static int pathmax = PATH_MAX;
#else
static int pathmax = 0;
#endif
#define MAX_PATH_GUESSED 1024
#ifndef LINE_MAX
#define LINE_MAX 2048
#endif
char *pathname;
char command[LINE_MAX], grep_cmd[LINE_MAX];

int ssu_do_grep(void)
{
    struct dirent *dirp;
    struct stat statbuf;
    char *ptr;
    DIR *dp;
    printf("%d: %s", buf);
}

void ssu_make_grep(int argc, char *argv[])
{
    int i;
}

int main(int argc, char *argv[])
{
    printf("usage: ./a.out <-CVbchilnsvwx> <-num> <-A num> <-B num> <-f file>
<-e> expr <directory>");
    ssu_make_grep(argc, argv);
    ssu_do_grep();
    exit(0);
}
//54~
// 2. 타겟 파일에 디렉토리가 올 수 있는 것을 제외하고 grep의 옵션 및 사용법을 따를 것
// 3. 타겟 파일이 디렉토리가 아닐 경우 system()을 사용하여 grep를 실행할 것
// 4. 타겟 파일이 디렉토리일 경우 모든 하위파일에서 키워드를 검색할 것
// 5. ssu_do_grep()함수에서 파일의 정보를 얻기 위해 lstat()을 한 번 사용하고 에러 처리를 위해 fprintf()를 사용할
// 것
// 6. ssu_do_grep()함수에서 opendir()을 한 번만 사용하고 에러 처리를 위해 fprintf()를 사용할 것
// 7. ssu_make_grep()함수에서 string.h에 있는 함수를 사용하여 grep_cmd를 만들 것
// 8. 컴파일 시 –D 옵션으로 pathmax 값을 입력받지 못할 경우 pathmax의 값을 pathconf를 사용하여 구할 것. 단,
// 에러가 발생할 경우 MAX_PATH_GUESSED를 사용할 것
// 9. pathname은 malloc()을 사용하여 메모리 공간을 할당받을 것