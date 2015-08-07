#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(){
	char buffer[50];
	// getcwd(buffer,50);
	pid_t pid = getpid();
	char symLink[20];
	sprintf(symLink, "/proc/%ld/cwd",(long)pid);	
	ssize_t size;
	size = readlink(symLink, buffer,50);
	buffer[(int)size] = '\0';
	printf("%s\n", buffer);
	exit(EXIT_SUCCESS);
}