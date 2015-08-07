#include "utility.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

char* trim(char* str){
	while(isspace(str[0])){
		str++;
	}
	return str;
}