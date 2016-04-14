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
node SLCreateNode(void *data,SortedListPtr list){
	node newNode = (node)malloc(sizeof(node));
	newNode->data = data;
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
		newNode = SLCreateNode(newObj,list);
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
			newNode = SLCreateNode(newObj,list);
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
	newNode = SLCreateNode(newObj,list);
	prev->next = newNode;
	return;
}

void insertFileData(SortedListPtr list,char* filename,int choice){
	node temp = list->head;

	while(temp !=NULL){
		//add new file node
		fileData newObj = (fileData)malloc(sizeof(newObj));
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
