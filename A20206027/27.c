#include <string.h>
#include <sys/stat.h>
#define DIRECTORY_SIZE MAXNAMLEN                             //디렉토리 이름 길이 매크로
#define isdigit(x) (x >= '0' && x <= '9') ? 1 : 0            //숫자 판단 매크로
#define MODE S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH //권한 매크로
int create_dir(int depth, char *cur_dir);                    //디렉토리 생성 함수
void writefile(char *in_f, char *out_f);                     // 파일을 복사하는 함수
void change_mod(const char *file_path);                      //모드를 변경하는 함수
char *fname = "ssu_test.txt";                                //생성하고 복사할 파일의 기본 이름
int o_flag = 0, e_flag = 0;                                  //e 옵션과 o옵션을 나타낼 플래그
int main(int argc, char *argv[])
{
    int opt;       //옵션인자를 받을 변수
    int depth = 0; //하위 디렉터리의 갯수를 받을 변수
    char cur_dir_name[DIRECTORY_SIZE] = {
        "\0",
    }; //현재 디렉토리 이름
    int fd;
    while ((opt = getopt(argc, argv, "e:o:")) != -1)
    {
        switch (opt)
        {
        case '?':
            break;
        }
    }
    if (argc < 3)
    {
    }
    else
        fprintf(stderr, "too many argv\n");
    if ((fd = creat(fname, MODE)) < 0)
    {
        fprintf(stderr, "creat error for %s \n", fname);
        exit(1);
    }
    else
        close(fd);
    if ()
    {
        fprintf(stderr, "mkdir error\n");
        exit(1);
    }
    create_dir(depth, cur_dir_name);
    exit(0);
}
int create_dir(int depth, char *cur_dir)
{
    struct stat dir_st;
    int i = 0;
    char tmp_filename[MAXNAMLEN] = {
        '\0',
    };
    while (cur_dir[i] != '\0')
        i++;
    if (stat(cur_dir, &dir_st) < 0)
    {
    }
    strcat(tmp_filename, cur_dir);
    if (o_flag)
    {
    }
    else if (e_flag)
    {
    }
    else if (!o_flag && !e_flag)
    {
    }
    if (depth == 0)
        return 0;
    return create_dir(depth - 1, cur_dir);
}
void writefile(char *in_f, char *out_f)
{
}
void change_mod(const char *file_path)
{
}

// 1. 각 함수가 정의된 헤더파일을 정확히 쓸 것
// 2. 명령어 뒤에는 인자로 숫자N(1~9)을 받는다고 가정
// 3. 처음 생성되는 디렉터리의 이름은 ‘0’(숫자)이며 하위 디렉터리는 ‘0 / N / N-1 / N-2 / .../ 0’ 식으로 생성
// 4. 하위 디렉터리는 N에는 ‘N-1’디렉터리 와 실행결과 <예시> 와 같이 권한이 0600인 ‘<N-1>ssu_test.txt’를
// 복사
// 5. ‘ssu_test.txt’ 파일의 복사는 선택적으로 하는 옵션으로는 –e 옵션과 –o 옵션이 있음
// 6. –e 옵션과 –o 옵션 뒤에는 숫자N을 인자로 받으며 기본 동작과 동일하게 N개의 하위 디렉터리를 만드나, –e
// 옵션이 있다면 짝수 디렉터리에 ‘<N-1>ssu_test.txt’ 파일을 복사하며 해당 모드 권한을 원본파일의 권한과
// 동일하게 MODE 매크로와 chmod를 사용하여 변경
// 7. 반대로 –o옵션은 홀수 디렉터리에 ‘<N-1>ssu_test.txt’ 파일을 복사