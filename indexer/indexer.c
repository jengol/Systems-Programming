
#include "indexer.h"

void printList(SortedListPtr list,char* outputFile){
	FILE* fp = fopen(outputFile,"w");

	if(fp == NULL){
		perror(outputFile);
		return;
	}
	fprintf(fp,"%s","{ \"list\": [\n");

	node temp = list->head;
	node filetemp;
	fileData x;

	while(1){
		fprintf(fp,"\t{ \"%s\" : [\n", (char*)(temp->data));
		filetemp = temp->fileList->head;
		while(filetemp!=NULL){
			x = (fileData)(filetemp->data);
			fprintf(fp,"\t\t{ \"%s\" : %d}\n",x->filename, x->frequency);
			filetemp = filetemp->next;
		}
		if(temp->next == NULL){
			fprintf(fp,"\t]}\n");
			break;
		}
		fprintf(fp,"\t]},\n");
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

		int a = ((fileData)one)->frequency;
		int b = ((fileData)two)->frequency;

		if(a<b || a==b){
			return -1;
		}
		else{
			return 1;
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
	//If the file Pointer is invalid, print and error
	if(fp == NULL){
		perror(filename);
		return;
	}

	char * line = NULL;
	size_t len = 0;
	size_t lineLength = 0;
	char* output = NULL;
	Tokenizer *ourTokenizer= NULL;

	//read stores the length of the line in the file
	while ((lineLength = getline(&line, &len, fp)) != -1) {
		//read instead of line
		ourTokenizer = TKCreate(line,lineLength-1);
		if (ourTokenizer == NULL) {
			printf("Error: Failed to Tokenize");
			return;
		}
		//Output will be NULL when it has reached the end of the line
		while (1) {
			output = TKGetNextToken(ourTokenizer);
			if(output){
				SLInsert(list,output,1);
			} else {
				break;
			}
		}
		//add fileData to file linked lists


		//reset the wordCount of each node in SL

//		TKDestroy(ourTokenizer);
		//		line = NULL;
	}
	insertFileData(list,filename,0);
	resetList(list);
	fclose(fp);

//		Print the SortedListPtr
		node tmp = list->head;
		while(tmp != NULL){
			printf("%s\n",(char*)(tmp->data));
			tmp = tmp->next;
		}
		printf("----------------------\n");
	return;

}

/*
 * indexProcess will recursively find all the files in the directory.
 * Then, it will call the function readFile to process the data.
 */
void indexProcess(char* path, SortedListPtr list){

	DIR* dir;
	struct dirent *ent;

	//If the directory is valid
	if ( (dir=opendir(path)) ) {
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
				//				printf("Within a directory:\t%s\n",next);
				//MAJOR INSTRUCTIONS
				readFile(next,list);
			}
		}
		closedir(dir);
	} else { //The directory is invalid
		//Check if it is a file
		FILE* fp;
		fp = fopen(path, "r");
		//If the file does not exist, print an error and return
		if(fp == NULL){
			perror(path);
			return;
		} else {
			//close file. It was will be reopened in readFile function
			fclose(fp);
			//			printf("filename:\t%s\n",path);
			readFile(path,list);
		}
	} 
	return;
}

int main(int argc, char **argv) {

	//Name of output file
//		char* outputFile = argv[1];
	//Name of the directory or file to index
//		char* path = argv[2];


	//Hard Code

	char* path = "/ilab/users/je283/Desktop/folder1";
	char* outputFile = "/ilab/users/je283/Desktop/output.txt";
	//List will contain all of the data describing the tokens and fileData struct
	SortedListPtr list = SLCreate(compare,destroyFreq);
	//Process the path into the list
	indexProcess(path,list);
	//Print the list into the output file
	printList(list,outputFile);

	return 0;
}



