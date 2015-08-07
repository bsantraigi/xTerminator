#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

typedef struct _node{
	char* val;
	struct _node* next;
} Node;

typedef struct _stack
{
	Node* top;
	int size;	
} Stack;

extern int errno;

char* split(char* dir);
char* pop(Stack* s);
void push(Stack* s, char* val);
char* peek(Stack* s);

int main(int argc, char *argv[]){
	struct stat st = {0};
	char *dirName = argv[0];
	char* r = strtok(dirName, " ");
	while(r != NULL){
		if (stat(r, &st) == -1) {
		    int ret = mkdir(r, 0700);
		    
		    if(ret == -1){
		    	perror("mkdir");
		    	if(errno == 2){
			    	// printf("Error No. %d\n", errno);
		    		Stack stack;
		    		struct stat st;
		    		stack.size = 0;
		    		char* dir1;
		    		do{
		    			// printf("Hid\n");
		    			dir1 = split(r);		    		
		    			// printf("Dir: %s\n", dir1);

			    		push(&stack, r);
			    		if(dir1 == NULL){
		    				break;
		    			}	    
			    		strcpy(r,dir1);			    		
			    		// printf("Create '%s' then '%s'\n", dir1, peek(&stack));
			    	}while(stat(dir1, &st) == -1);

			    	while(stack.size > 0){
			    		printf("HI\n");
			    		char* t = pop(&stack);
			    		printf("mkdir %s\n", t);
			    		ret = mkdir(t, 0700);
				    	if(ret == -1){
				    		perror("mkdir");
				    	}
			    	}
		    	}else{
		    		break;
		    	}
		    }
		}else{
			printf("Directory %s already exists.\n", r);
		}
		r = strtok(NULL, " ");
		// printf("r is %s\n", r);
	}
	return 0;
}

char* split(char* dir){
	//dir is the final call
	//before that returned value must be created
	int s = strlen(dir);
	int i = s;
	while(dir[--i] != '/'){
		if(i==0){
			break;
		}
	}
	if(i == s - 1){
		fprintf(stderr, "Bad directory name.\n");
		dir[i] = '\0';
		return dir;
	}else if(i!=0){
		char *r;
		r = (char*)malloc(s*sizeof(char));
		strcpy(r, dir);
		r[i] = '\0';
		return r;
	}else{
		return NULL;
	}
}

void push(Stack* s, char* val){
	Node* n = (Node*)malloc(sizeof(Node));
	n->val = (char*)malloc((strlen(val) + 2)*sizeof(char));
	strcpy(n->val, val);
	n->next = s->top;
	s->top = n;
	s->size++;
}

char* pop(Stack* s){
	if(s->size>0){
		Node* r = s->top;
		s->top = s->top->next;
		s->size--;
		return r->val;
	}else{
		return NULL;
	}
}

char* peek(Stack* s){
	if(s->size > 0){
		return s->top->val;
	}else{
		return "";
	}
}