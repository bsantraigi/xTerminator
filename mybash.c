#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "utility.h"

extern int errno;

char* readLine(char* string, int BUFF_SIZE);

int main(){
	char shellLoc[256];
	getcwd(shellLoc,50);

	char pwd[256];
	sprintf((char*)pwd, "%s/mypwd", shellLoc);

	char ls[256];
	sprintf((char*)ls, "%s/myls", shellLoc);

	char mkdir[256];
	sprintf((char*)mkdir, "%s/mymkdir", shellLoc);

	char rm[256];
	sprintf((char*)rm, "%s/myrm", shellLoc);

	char tail[256];
	sprintf((char*)tail, "%s/mytail", shellLoc);

	char mv[256];
	sprintf((char*)mv, "%s/mymv", shellLoc);

	char ps[256];
	sprintf((char*)ps, "%s/myps", shellLoc);


	char *command;
	char *args;
	char temp[256];
	command = (char *)malloc(256*sizeof(char));
	pid_t pid;
	int status;

	while(1){
		printf("root@PC (%ld) > ", (long)getpid());
		// scanf("%s", command);
		command = readLine(command, 256);
		// printf("%s\n", command);
		strcpy(temp, command);
		strtok(temp, " ");
		if(strtok(NULL, " ") != NULL){
			// printf("Temp: %s\n", temp);
			args = command + strlen(strtok(command, " ")) + 1;
		}else{
			args = "";		
		}
		// printf("CMD: %s, ARGS: %s\n", command, args);
		
		if(strcmp(command,"mypwd") == 0){
			switch(pid = fork()){
				case 0:
				//Inside child process

				execl(pwd, args, (char*)NULL);
				perror("execv");
				break;
				case -1:
				perror("fork");
				break;
				default:				
				waitpid(pid,&status,0);
			}
		}else if(strcmp(command,"myls") == 0){
			switch(pid = fork()){
				case 0:
				//Inside child process
				execl(ls, args, (char*)NULL);
				perror("execl");
				break;
				case -1:
				perror("fork");
				break;
				default:					
				waitpid(pid,&status,0);
			}
		}else if(strcmp(command,"myps") == 0){
			switch(pid = fork()){
				case 0:
				//Inside child process
				execl(ps, args, (char*)NULL);
				perror("execl");
				break;
				case -1:
				perror("fork");
				break;
				default:					
				waitpid(pid,&status,0);
			}
		}else if(strcmp(command,"myrm") == 0){
			switch(pid = fork()){
				case 0:
				//Inside child process
				execl(rm, args, (char*)NULL);
				perror("execl");
				break;
				case -1:
				perror("fork");
				break;
				default:					
				waitpid(pid,&status,0);
			}
		}else if(strcmp(command,"mytail") == 0){
			switch(pid = fork()){
				case 0:
				//Inside child process
				args = trim(args);
				int i = 0, j = 0;

				char* num = strtok(args, " ");

				int count = atoi(num);
				if(count == 0){
					execl(tail, args, (char*)NULL);
				}else if(num == args || num!=NULL){
					execl(tail, num, args+strlen(num) + 1, (char*)NULL);
					perror("execl");
				}
				break;
				case -1:
				perror("fork");
				break;
				default:					
				waitpid(pid,&status,0);
			}
		}else if(strcmp(command,"mymkdir") == 0){
			switch(pid = fork()){
				case 0:
				//Inside child process
				execl(mkdir, args, (char*)NULL);
				perror("execl");
				break;
				case -1:
				perror("fork");
				break;
				default:					
				waitpid(pid,&status,0);
			}
		}else if(strcmp(command,"mymv") == 0){
			switch(pid = fork()){
				case 0:
				//Inside child process
				execl(mv, args, (char*)NULL);
				perror("execl");
				break;
				case -1:
				perror("fork");
				break;
				default:					
				waitpid(pid,&status,0);
			}
		}else if(strcmp(command,"mycd") == 0){
			// printf("Chaning folder to %s\n", args);
			if(chdir(args) == -1){
				perror("chdir");
			/*	switch(errno){
					case ENOTDIR:
						printf("ERROR: That's not a folder.\n");
					break;
					case EBADF:
						printf("ERROR: Bad folder name.\n");
					break;
					default:
						printf("ERROR: Cannot change directory.\n");
				}*/
			}else{
				// printf("Hi\n");
			}
		}else if(strcmp(command,"myps") == 0){
			printf("Process id: %ld\n", (long)getpid());
		}else if(strcmp(command,"exit") == 0){
			// printf("Exiting from process id:%ld\n", (long)getpid());
			exit(0);
		}else if(strcmp(command,"") != 0){
			fprintf(stderr, "%s is not a valid command.\n", command);
		}
	}
	return 0;
}

char* readLine(char* string, int BUFF_SIZE){
	int i = 0;
	char c;
	while((c = getchar()) != '\n' ){
		if(i >= BUFF_SIZE - 1){
			fprintf(stderr, "ERROR: Command is too long...\n");
			return NULL;
		}
		string[i++] = c;
	}

	string[i++] = '\0';
	return string;
}