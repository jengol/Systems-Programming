//#include "tokenizer.h"

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


char *getSubString(char * String, int begin, int end){

	int length = end - begin;
	char *subString = (char*)malloc(sizeof(char)*length+1);
	int i;
	for (i = 0; i < length; i++) {
		subString[i] = String[begin];
		begin++;
		printf("index is currently: %d\n",i);
	}
	printf("index is currently: %d\n",i);
	subString[i] = '\0';
	return subString;
}

int main(int argc, char **argv) {


	char* s = "hello";

	char* x = (char*)malloc(sizeof(char)*3);
	int i;
	for (i = 0; i < 3; ++i) {
		x[i] = 'a';
	}
	printf("the string x is: %s\n",x);


	char* substring = getSubString(s,2,4);
	printf("%s",substring);


	return 0;
}
