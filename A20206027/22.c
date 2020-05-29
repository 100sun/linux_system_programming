#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

int main(int argc, char* argv[])
{
	if(argc < 3){
		fprintf(stderr, "usage : %s <file1><file2>...<fileN>\n",argv[0]);
		exit(1);
	}

	// make new link to the file argv[1] pointing
	if(link(argv[1], argv[2]) == -1){
		fprintf(stderr, "link error for %s\n", argv[1]);
		exit(1);	
	}
}

// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/stat.h>
// #include <sys/types.h>
// #include <stdio.h>
// #include <stdlib.h>

// int main(int argc, char *argv[])
// {
//     struct stat statbuf;
//     ino_t inode;
//     if (argc != 3)
//     {
//         fprintf(stderr, "argc != 3\n");
//         exit(1);
//     }

//     if (link(argv[1], argv[2]) == -1)
//     {
//         fprintf(stderr, "link error\n");
//         exit(1);
//     }
//     stat(argv[1], &statbuf);
//     printf("%s's inode = %ld -> ", argv[1], statbuf.st_ino);
//     stat(argv[2], &statbuf);
//     printf("%s's inode = %ld\n", argv[2], statbuf.st_ino);

//     if (unlink(argv[1]) == -1)
//     {
//         fprintf(stderr, "unlink error");
//         exit(1);
//     }
//     exit(0);
// }