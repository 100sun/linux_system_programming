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
