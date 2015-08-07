#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include "utility.h"


int main(int argc, char *argv[])
{
	if(argc >= 1){
		argv[0] = trim(argv[0]);
		char *source = strtok(argv[0]," ");
		char *dest = strtok(NULL," ");
		dest = trim(dest);
		if(strlen(source) != 0 && strlen(dest) != 0){
			if(rename(source, dest) == -1){
				perror("rename");
			}
		}
	}
	return 0;
}