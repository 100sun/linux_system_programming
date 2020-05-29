#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef struct _person
{
    char name[10];
    int age;
    double height;
} Person;

int main(void)
{
    FILE *fp;
    int i, res;
    Person ary[3] = {{"Hong GD", 500, 175.4},
                     {"Lee SS", 350, 180.0},
                     {"King SJ", 500, 178.6}};

    if ((fp = fopen("ftest.txt", "w+")) == NULL)
    {
        fprintf(stderr, "fopen error\n");
        exit(1);
    }
    for (int i = 0; i < 3; i++)
        fwrite(&ary[i], sizeof(struct _person), 1, fp);

    rewind(fp);
    Person tmp;
    printf("[ First print]\n");
    while (!feof(fp))
    {
        fread(&tmp, sizeof(struct _person), 1, fp);
        printf("%s %d %.2lf\n", tmp.name, tmp.age, tmp.height);
    }
    fclose(fp);
    
    if ((fp = fopen("ftest.txt", "r")) == NULL)
    {
        fprintf(stderr, "fopen error\n");
        exit(1);
    }
    printf("[ Second print]\n");
    while (!feof(fp))
    {
        fread(&tmp, sizeof(struct _person), 1, fp);
        printf("%s %d %.2lf\n", tmp.name, tmp.age, tmp.height);
    }
    fclose(fp);
    exit(0);
}
