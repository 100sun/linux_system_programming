#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for close();
#include <fcntl.h> // for oflag
#include <sys/stat.h> // for mode 
#include <sys/types.h> // for mode_t

int main(void){
	char *fname = "ssu_test.txt";
	int fd; // file descripter

	if((fd = creat(fname, 0666)) < 0) { 
	// ssu_text를 rw-rw-rw- 즉, users, group, others 의 executions 권한만 부여하지 않은채 생성
		fprintf(stderr, "creat error for %s\n", fname);
		exit(1); // fail
	}
	else{
		printf("Success!\nFilename : %s\nDescriptor : %d\n", fname, fd);
		close(fd); // open<->close => creat<->close / open() contains creat()
	}
	exit(0); // success
}
