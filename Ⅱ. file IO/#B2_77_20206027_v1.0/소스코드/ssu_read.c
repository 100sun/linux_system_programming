// printing values by the typed record
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
	int record_num;

	// arguments processing
	if(argc < 2){ // argv[1] == program name -> at least one 
		fprintf(stderr, "Usage : %s file\n", argv[0]);
		exit(1);
	}

	// open	
	if((fd = open(argv[1], O_RDONLY)) < 0){ // file open in read-only
		fprintf(stderr, "open error for %s\n", argv[1]);
		exit(1);
	}

	while(1){
		printf("Enter record number : ");
		scanf("%d", &record_num);

		if(record_num < 0) break;
		
		// move offset to the position of input record
		if(lseek(fd, (long)record_num * sizeof(record), 0) < 0){ // offset == (record_num * size of record) 
			fprintf(stderr, "lseek error\n");
			exit(1);
		}

		// record read 
		if(read(fd, (char *)&record, sizeof(record)) > 0) // read up to size of ssu_employee from argv[1] fd into the buffer starting at &record
			printf("Employee : %s Salary : %d\n", record.name, record.salary);
		else
			printf("Record %d not found\n", record_num); // read error
	}

	close(fd);
	exit(0);
}
			
