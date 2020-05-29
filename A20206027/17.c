// 1. 각 함수가 정의된 헤더파일을 정확히 쓸 것
// 8. main()의 인자의 에러 처리를 위하여(프로그램 사용법) fprintf()를 사용할 것
// 2. link(), unlink()를 각각 한 번씩 사용할 것
// 3. link(), unlink()의 에러 처리를 위해 fprintf()를 사용할 것
// 4. 프로그램의 실행은 “./a.out [arg1] [arg2]”와 같이 반드시 인자 두개를 받아야 하며, arg1에 해당하는 파일을
// arg2에 해당하는 경로로 이동하거나 이름을 변경해야 함
// 5. 실행결과와 동일한 포맷으로 gettimeofday() 함수를 사용하여 프로그램 실행 시간을 출력해야 함. 단, 출력된
// 결과 값은 달라질 수 있음.
// 6. 측정된 수행시간은 단 한번의 printf() 함수를 사용할 것
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define SEC_TO_MICRO 1000000

int main(int argc, char *argv[])
{
    struct timeval begin_t, end_t;
    gettimeofday(&begin_t, NULL);

    // if (link(argv[1], argv[2]) < 0)
    // {
    //     fprintf(stderr, "link error\n");
    //     exit(1);
    // }
    if (unlink(argv[1]) < 0)
    {
        fprintf(stderr, "link error\n");
        exit(1);
    }

    gettimeofday(&end_t, NULL);
    ssu_runtime(&begin_t, &end_t);

    exit(0);
}

void ssu_runtime(struct timeval *begin_t, struct timeval *end_t)
{
    end_t->tv_sec -= begin_t->tv_sec;

    if (end_t->tv_usec < begin_t->tv_usec)
    {
        end_t->tv_sec--;
        end_t->tv_usec += SEC_TO_MICRO;
    }

    end_t->tv_usec -= begin_t->tv_usec;
    printf("Runtime: %ld:%01ld(sec:usec)\n", end_t->tv_sec, end_t->tv_usec);
}
