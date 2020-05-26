#include <stdio.h>
#include <stdlib.h>

void ssu_printenv(char *label, char ***envpp);
extern char **environ;

int main(int argc, char *argv[], char *envp[])
{
	ssu_printenv("Initially", &envp);// print environmental variables
	putenv("TZ=PST8PDT"); // add the string to the env
	
	ssu_printenv("After changing TZ", &envp);// print environmental variables
	putenv("WARNING=Don't use envp after putenv()");// add the string to the env
	
	ssu_printenv("After setting a new variable", &envp);// print environmental variables
	printf("value of WARNING is %s\n", getenv("WARNING"));
	
	exit(0);
}

void ssu_printenv(char *label, char ***envpp) { 
	char **ptr;
	printf("---- %s ---\n", label);
	printf("envp is at %8o and contains %8o\n", envpp, *envpp);
	printf("environ is at %8o and contains %8o\n", &environ, environ);
	printf("My environment variable are:\n");
	for (ptr = environ; *ptr; ptr++)
		printf("(%8o) = %8o -> %s\n", ptr, *ptr, *ptr);
	printf("(%8o) = %8o\n", ptr, *ptr);
}
