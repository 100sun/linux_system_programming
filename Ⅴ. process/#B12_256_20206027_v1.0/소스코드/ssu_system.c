#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(void)
{
    printf("before system()\n");
    system("pwd"); // execute the shell command
    printf("after system()\n");
    exit(0);
}
