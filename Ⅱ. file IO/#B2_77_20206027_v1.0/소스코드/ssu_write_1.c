// stdout buf read from stdin
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 

#define BUFFER_SIZE 1024

int main(void){
	char buf[BUFFER_SIZE];
	int length;

	// ex. opacity of password
	length = read(0, buf, BUFFER_SIZE); // 0 : standart input
	write(1, buf, length); // 1 : standard ouput -> print what you write on the keyboard
	exit(0);
}
