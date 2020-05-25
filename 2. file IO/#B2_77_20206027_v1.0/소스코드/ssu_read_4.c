#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 

#define TABLE_SIZE 128
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]){ // argc : number of arguments / argv : array of arguments 
	// create table
	static struct {
		long offset;
		int length;
	} table [TABLE_SIZE];
	
	char buf[BUFFER_SIZE];
	long offset;	int entry;
	int i;		int length; // for while loop
	int fd;

	// arguments processing
	if(argc < 2){ // argv[1] == program name -> at least one 
		fprintf(stderr, "Usage : %s file\n", argv[0]);
		exit(1);
	}

	// open file
	if((fd = open(argv[1], O_RDONLY)) < 0){ 
		fprintf(stderr, "open error for %s\n", argv[1]);
		exit(1);
	}

	entry = 0;	offset = 0;
	
	// during current line : length++ of "n"
	// at the moment of new line : offset adoption of "n+1"
	// afterwards : length adoption
	while((length = read(fd, buf, BUFFER_SIZE)) > 0){ // length <= 0 : no more char to read

		for(i=0; i < length; i++){
			table[entry].length++; // change length by one char in each table
			offset++; // accumulation of offset in the overall fd

			if(buf[i] == '\n') {
				//printf("new line!\n");
				table[++entry].offset = offset; // change offset by each table
			}
			//printf("entry : %d offset : %ld table[%d].length = %d table[%d].offset = %ld\n", entry, offset, entry, table[entry].length, entry, table[entry].offset);
		}
	}

	#ifdef DEBUG
		for(i=0; i < entry; i++)
			printf("%d : %ld, %d\n", i+1, table[i].offset, table[i].length);
	#endif
		
	while(1){
		// input
		printf("Enter line number : ");
		scanf("%d", &length);
		
		if(--length < 0) break;
		
		// read the line number
		lseek(fd, table[length].offset, 0); // move to the front of table[line number]
		if(read(fd, buf, table[length].length) <= 0) // read up to the size of the lengt of table[line number] into buf which will printf 
		       	continue; // until here, go back to top

		buf[table[length].length] = '\0'; // at the end of the table, confirm that it is end of string (NULL)
		printf("%s", buf);
	}

	close(fd);
	exit(0);
}
			
