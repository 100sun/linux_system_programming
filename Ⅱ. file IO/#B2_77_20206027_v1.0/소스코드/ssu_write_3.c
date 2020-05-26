#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include "ssu_employee.h"

int main(int argc, char *argv[]){ // argc : number of arguments / argv : array of arguments 
	struct ssu_employee record;
	int fd;

	// arguments processing
	if(argc < 2){ // argv[1] == program name -> at least one 
		fprintf(stderr, "Usage : %s file\n", argv[0]);
		exit(1);
	}

	// open	
	if((fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, 0640)) < 0){ // rw-r-----
		fprintf(stderr, "open error for %s\n", argv[1]);
		exit(1);
	}

	while(1){
		// scan input values of record
		printf("Enter employee name <SPACE> salary: ");
		scanf("%s", record.name);
		if(record.name[0] == '.') break; // user wanted to stop entering 
		scanf("%d", &record.salary);
		record.pid = getpid();
		
		// write the value on the memory
		write(fd, (char*)&record, sizeof(record));
	}	
	
	close(fd);
	exit(0);
}
