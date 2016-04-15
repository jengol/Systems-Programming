#include "sorted-list.h"
#include <stdio.h>


SortedListPtr SLCreate(CompareFuncT cf, DestructFreq dfreq){

	SortedListPtr list = (SortedListPtr)malloc(sizeof(SortedListPtr));
	list->head = NULL;
	list->cmp = cf;
	list->dfreq = dfreq;
	return list;	
}

//creates node using node struct, sets next pointer to null and points to data passed into function
node SLCreateNode(void *data,SortedListPtr list,int choice){
	node newNode = (node)malloc(sizeof(node));


	void* temp;
	//the data is a char*
	if(choice == 1){
		temp = malloc(sizeof(char*)*(strlen((char*)data)+1));
		strcpy((char*)temp,(char*)data);
	} else if(choice == 0){// the data is a struct fileData
		temp = malloc(sizeof(struct fileData));

		((fileData)temp)->filename = malloc(sizeof(char*)*(strlen(((fileData)data)->filename)+1));
		strcpy(((fileData)temp)->filename,((fileData)data)->filename);
		((fileData)temp)->frequency = ((fileData)data)->frequency;

	}

	newNode->data = temp;
	newNode->next = NULL;
	newNode->wordcount = 1;
	newNode->fileList = NULL;
	return newNode;
}

void SLInsert(SortedListPtr list,void *newObj,int choice){

	//Basic error check
	if(list == NULL){
		return;
	}

	//Assume a new node will be created
	//If not used, it means that newObj already exists
	//newNode will be freed

	node newNode;
	//If the list is not initialized
	if (list->head == NULL){
		newNode = SLCreateNode(newObj,list,choice);
		list->head = newNode;
		return;
	}

	//Compare value returned from the compare function
	int compVal;

	//prev is used to keep a pointer to the last node if ptr reaches NULL
	node prev = NULL;
	node ptr = list->head;
	do {
		compVal = list->cmp(ptr->data, newObj,choice);
		if(compVal == -1){
			newNode = SLCreateNode(newObj,list,choice);
			if(ptr == list->head){
				newNode->next = list->head;
				list->head = newNode;
				return;
			}
			newNode->next = ptr;
			prev->next = newNode;
			return;
		} else if (compVal == 0) {
			ptr->wordcount++;
			//If the data already exists free the node that was created already
			return;
		} else { //compVal == 1: the data comes after
			prev = ptr;
			ptr = ptr->next;
		}
	} while (ptr!= NULL);

	//prev will be pointing to the last node
	newNode = SLCreateNode(newObj,list,choice);
	prev->next = newNode;
	return;
}

void insertFileData(SortedListPtr list,char* filename,int choice){

	if(list == NULL){
		printf("List is NULL");
		return;
	}


	node temp = list->head;
	fileData newObj;
	while(temp !=NULL){

		if (temp->wordcount == 0) {
			temp = temp->next;
			continue;
		}

		//initialize
		if (temp->fileList == NULL) {
			temp->fileList = SLCreate(list->cmp,list->dfreq);
		}

		newObj = (fileData)malloc(sizeof(struct fileData));

		newObj-> filename = filename;
		newObj-> frequency = temp->wordcount;
		SLInsert(temp->fileList,newObj,0);

		temp = temp->next;
	}
	return;
}

void resetList(SortedListPtr list){
	node temp = list->head;

	while(temp!= NULL){
		temp->wordcount = 0;
		temp = temp->next;
	}
	return;
}

void destroyList(SortedListPtr list){

	node temp1 = list->head;
	node temp2;
	node ftemp1, ftemp2;
	while(temp1!=NULL){
		ftemp1 = temp1->fileList->head;
		while(ftemp1 != NULL){
			ftemp2 = ftemp1->next;
			list->dfreq(ftemp1->data);
			free(ftemp1);
			ftemp1 = ftemp2;
		}
		temp2 = temp1->next;
		free(temp1);
		temp1=temp2;
	}
	return;
}
