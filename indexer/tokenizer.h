#ifndef TOKEN_H_
#define TOKEN_H_

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

struct Tokenizer_ {
	int index;
	char* token;
};
typedef struct Tokenizer_ Tokenizer;

Tokenizer *TKCreate(char * input);

void TKDestroy(Tokenizer * tk);

char *getSubString(char * String, int begin, int end);

char* TKGetNextToken( Tokenizer * tk );

#endif /* TOKEN_H_ */

