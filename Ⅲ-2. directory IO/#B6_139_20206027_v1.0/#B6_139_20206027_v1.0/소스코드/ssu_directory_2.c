#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>

#ifdef PATH_MAX
static int pathmax = PATH_MAX;
#else
static int pathmax = 0;
#endif

#define MAX_PATH_GUESSED 1024

#ifndef LINE_MAX
#define LINE_MAX 2048
#endif

char *pathname;
char command[LINE_MAX], grep_cmd[LINE_MAX];

int ssu_do_grep(void)
{
	struct dirent *dirp;
	struct stat statbuf;
	char *ptr;
	DIR *dp;

	// symbolic link file to statbuf 
	if(lstat(pathname, &statbuf)<0){ 
		fprintf(stderr, "lstat error for %s\n", pathname);
		return 0;
	}

	// if it is just regular file ( not directory )
	if(S_ISDIR(statbuf.st_mode)==0){ 
		sprintf(command, "%s %s", grep_cmd, pathname); // remember cmd
		printf("%s : \n", pathname); 
		system(command); // grep() by system()
		return 0;
	}
	
	ptr = pathname + strlen(pathname);
	*ptr++ = '/'; //'/' insert
	*ptr = '\0'; // EOF 

	if((dp = opendir(pathname))==NULL){ //directory open
		fprintf(stderr, "opendir error for %s\n", pathname);
		return 0;
	}

	while((dirp = readdir(dp)) != NULL)
		if(strcmp(dirp->d_name, ".") && strcmp(dirp->d_name, "..")){ //filename != . or ..
			strcpy(ptr, dirp->d_name); // filename copy

			if(ssu_do_grep() < 0) // do grep 
				break;
		}

	ptr[-1] = 0;
	closedir(dp);
	return 0;
}

void ssu_make_grep(int argc, char *argv[])
{
	int i;
	strcpy(grep_cmd, " grep"); // grep command copy 

	for(i=1; i<argc-1; i++){
		strcat(grep_cmd, " "); // append blank
		strcat(grep_cmd, argv[i]); // append the pathname
	}
}

int main(int argc, char *argv[])
{

	if(argc<2){ 
		fprintf(stderr, "usage: %s <-CVbchilnsvwx> <-num> <-A num> <-B num> <-f file> \n"
				"		<-e> expr <directory>\n", argv[0]);
		exit(1);
	}

	if(pathmax==0){ // if PATH_MAX is not defined
		if((pathmax = pathconf("/", _PC_PATH_MAX)) < 0) // if path == cwd : return the maxium bytes of pathname
			pathmax = MAX_PATH_GUESSED; // if error : allocate just random value
		else
			pathmax++;
	}

	if((pathname = (char*)malloc(pathmax+1)) == NULL){ //pathname memory allocation 
		fprintf(stderr, "malloc error\n");
		exit(1);
	}

	strcpy(pathname, argv[argc-1]); // copy the file path from pathname
	ssu_make_grep(argc, argv); // making command "grep"	
	ssu_do_grep(); // do the command "grep"
	exit(0);

}
