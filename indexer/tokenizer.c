#include "tokenizer.h"


/* The tokenizer holds the entire string that will be parsed into tokens
 * index is used and updated to keep track of the position in the tokenizer string
 */

Tokenizer *TKCreate(char * input,int len) {
	Tokenizer *ourTokenizer=(Tokenizer*)malloc(sizeof(Tokenizer));
	ourTokenizer->token = input;
	ourTokenizer->tokenLength = len;
	ourTokenizer->index = 0;
	return ourTokenizer;
}

void TKDestroy( Tokenizer * tk ) {
	free(tk);
}

//getSubString returns token from input String

char *getSubString(char * String, int begin, int end){

	int length = end - begin;
	char *subString = (char*)malloc(sizeof(char)*length+1);

	int i;
	for (i = 0; i < length; i++) {
		subString[i] = String[begin];
		begin++;
	}
	subString[i] = '\0';
	return subString;
}

/*
 * TKGetNextToken returns a string (delimited by '\0')
 * containing the token.  Else it returns 0.
 */

char* TKGetNextToken(Tokenizer * input){
	//returned token
	char* ret = NULL;

	int i = input->index;
	//If the index has reached the end of input
	if(i == input->tokenLength){
		return NULL;
	}
	//current character in the Tokenizer's token
	char current = input->token[i];

	if (isalpha(current)) {
		//next character
		current = input -> token[++i];
		//while the the current character is alphanumeric
		//updates index to find the end of token
		while (isalnum(current)) {
			current = input->token[++i];
		}
		//extracts the token from the substring
		ret = getSubString(input->token,input->index,i);
		input->index = i;
		return ret;
	} else {
		input->index++;
		ret = TKGetNextToken(input);
	}

	return ret;
}
