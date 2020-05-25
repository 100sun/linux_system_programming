//p70
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for file descripter
#include <fcntl.h> // for oflag
#include <sys/stat.h> // for mode 
#include <sys/types.h> // for mode_t

int main(void){
	char *fname = "ssu_test.txt";
	int fd; // file descripter

	if((fd = creat(fname, 0666)) < 0) { 
	// ssu_test를 rw-rw-rw- 즉, users, group, others 의 executions 권한만 부여하지 않은채 생성
		fprintf(stderr, "creat error for %s\n", fname);
		exit(1); // fail
	}
	else{
		close(fd); // you did first open so you have to close it!
		fd = open(fname, O_RDWR); 
		// if you want to read again and make it readable and writable, you have to use open() / I don't want to change the mode so I just use open() with 2 parameters
		printf("Succeeded!\n<%s> is new readable and writable\n", fname);
	}
	exit(0); // success
}
