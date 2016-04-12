#include "tokenizer.h"


/* The tokenizer holds the entire string that will be parsed into tokens
 * index is used and updated to keep track of the position in the tokenizer string
 */

Tokenizer *TKCreate(char * input) {
	Tokenizer *ourTokenizer=(Tokenizer*)malloc(sizeof(Tokenizer));
	ourTokenizer->token = input;
	ourTokenizer->index = 0;
	return ourTokenizer;
}

void TKDestroy( Tokenizer * tk ) {
	free(tk);
}

//getSubString returns token from input String

char *getSubString(char * String, int begin, int end){

	int length = end - begin;
	char *subString = (char*)malloc(sizeof(char)*length);

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

char* TKGetNextToken( Tokenizer * token ) {
	//nextT stores the desired token
	char* nextToken;

	int index = token -> index;
	//current is updated using the index of the tokenizer String as the function points to different chars
	char current = token -> token[index];

	//skips over white spaces and non asqii
	if (isspace(current) != 0 || ispunct(current) != 0 || isdigit(current) != 0) {
		index++;
		token -> index = index;
		return 0;	
	}

	//not sure if need this check
	//returns 0 so nothing is printed if the current char is the null termination that signals the end of the string.
	if (current == '\0') {
		return 0;
	}

	if (isalpha(current) != 0) {
		index++;
		current = token -> token[index];
		while (isalnum(current) != 0) {
			index++;
			current = token -> token[index];
		}
		nextToken = getSubString(token -> token, token->index, index);
		token -> index = index;
		return nextToken;
	}

//	if(isdigit(current) != 0){
//		idx ++;
//		current = tk-> tokenStr[idx];
//		while(isdigit(current) != 0){
//			idx ++;
//			current = tk-> tokenStr[idx];
//		}
//		nextT = getSubString(tk -> tokenStr, tk->index, idx);
//		tk -> index = idx;
//		return nextT;
//	}
	return NULL;
}
