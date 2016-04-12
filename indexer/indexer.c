
#include "indexer.h"

void printList(SortedListPtr list,char* outputFile){

	FILE* fp = fopen(outputFile,"w");
	printf("hi");
	fprintf(fp,"%s","{ list: [\n");

	node temp = list->head;
	node filetemp;
	fileData x;

	while(temp != NULL){
		fprintf(fp,"\t{ %s : [\n", (char*)(temp->data));
		filetemp = temp->fileList->head;
		while(filetemp!=NULL){
			x = (fileData)(filetemp->data);
			if(x->frequency != 0){
				fprintf(fp,"\t\t{ %s : %d}\n",x->filename, x->frequency);
			}
			filetemp = filetemp->next;
		}
		fprintf(fp,"\t]}\n");
		temp = temp->next;
	}

	fprintf(fp,"]}\n");
	fclose(fp);
	return;
}

/*Returns -1 if first < second
 * 		  0 if first == second
 * 		  1 if first > second
 */

int compare(void* one, void* two, int choice){
	//Do checking statement
	if(choice == 1){
		char f;
		char s;

		char * first = (char*)one;
		char * second = (char*)two;

		int i;
		for(i = 0;i<strlen(second);i++){
			//if the first word is shorter than the second word
			if( (first[i]) == '\0'){
				return 1;
			}

			//char at index i of first
			f = tolower(first[i]);
			//char at index i of second
			s = tolower(second[i]);

			//in tolower(), if the character is not a Capital, it remains unchanged
			if(f < s){
				return 1;
			} else if(f > s) {
				return -1;
			}
		}
		if(strlen(first)==strlen(second)){
			return 0;
		}
		return -1;
	} else if(choice == 0) {

		int a = *(int*)one;
		int b = *(int*)two;

		if(a<b || a==b){
			return 1;
		}
		else{
			return -1;
		}

	}

	//This line should not be reached
	return 0;
}

void destroyFreq(void* data){
	fileData f = (fileData)data;
	free(f);
	return;
}

void readFile(char* filename,SortedListPtr list){
	FILE* fp;
	fp = fopen(filename, "r");
	//If the file Pointer is NULL, then return NULL
	if(fp == NULL){
		return;
	}

	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	char* output = NULL;
	Tokenizer *ourTokenizer= NULL;


	while ((read = getline(&line, &len, fp)) != -1) {

		ourTokenizer = TKCreate(line);
		if (ourTokenizer == 0) {
			printf("Error: Malloc failed to create TokenizerT");
			return;
		}
		while (ourTokenizer->token[ourTokenizer->index] != '\0') {
			output = TKGetNextToken(ourTokenizer);
			//THIS SHOULD BE THE MAX LENGTH OF A LINE
			//			char *output = (char*)malloc(sizeof(char)*50);
			//			strcpy(output,TKGetNextToken(ourTokenizer));
			//Null check
			if(output){
				SLInsert(list,output,1);
				//printf("%s\n",output);
			}

		}
		//add fileData to file linked lists
		insertFileData(list,filename,0);
		//reset each wordCount to 0
		resetList(list);
		TKDestroy(ourTokenizer);
		line = NULL;
	}

	fclose(fp);

	/*Print the SortedListPtr
	node tmp = list->head;
	int i = 0;
	while(tmp != NULL){
		printf("%s\n",tmp->data);
		tmp = tmp->next;
	}*/
	return;

}

/*
 * indexProcess will list all the files within every directory recursively.
 * Then, it will call the function readFile to process the data
 */
void indexProcess(char* path, SortedListPtr list){

	DIR* dir;
	struct dirent *ent;

	if ( (dir=opendir(path)) != NULL) {
		while((ent = readdir(dir)) != NULL){
			if(ent->d_type == DT_DIR &&
					strcmp(ent->d_name, ".") != 0 &&
					strcmp(ent->d_name, "..") != 0){
				char* next = malloc(strlen(path)+strlen(ent->d_name)+2);
				strcpy(next,path);
				strcat(next,"/");
				strcat(next,ent->d_name);
				indexProcess(next,list);
			} else if (ent->d_type == DT_REG &&
					strcmp(ent->d_name, ".DS_Store") != 0) {
				char* next = malloc(strlen(path)+strlen(ent->d_name)+2);
				strcpy(next,path);
				strcat(next,"/");
				strcat(next,ent->d_name);
				//printf("%s\n",next);
				//MAJOR INSTRUCTIONS
				readFile(next,list);
			}
		}
		closedir(dir);
	} else {
		//If directory name is invalid, print an error.
		perror(path);
		readFile(path,list);
	} 

}

int main(int argc, char **argv) {

	//Name of output file
	char* outputFile = argv[1];
	//Name of the directory or file to index
	char* path = argv[2];

	//List will contain all of the data describing the tokens and fileData struct
	SortedListPtr list = SLCreate(compare,destroyFreq);
	//Process the path into the list
	indexProcess(path,list);
	//Print the list into the output file
	printList(list,outputFile);
	return 0;
}



