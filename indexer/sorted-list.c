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
	newNode->fileList = SLCreate(list->cmp,list->dfreq);
	return newNode;
}

void SLInsert(SortedListPtr list,void *newObj,int choice){

//	node front = list->head;


	//If the list is not initialized
	if (list->head == NULL){
		node newNode = SLCreateNode(newObj,list);
		list->head = newNode;
		return;
	}
	//If the newObj comes before the head node
	if (list->cmp(list->head->data, newObj,choice) == -1){
		node newNode = SLCreateNode(newObj,list);
		newNode->next = list->head;
		list->head = newNode;
		return;
	}
	//If the list only has one node and the newObj comes after head node
	if((list->cmp(list->head->data, newObj,choice) == 1) && list->head->next == NULL){
		node newNode = SLCreateNode(newObj,list);
		newNode->next = list->head->next;
		list->head->next = newNode;
		return;
	}

	node temp = list->head;

	while(temp->next != NULL){
		if(list->cmp(temp->next->data, newObj,choice)!= 0){
			if(list->cmp(temp->next->data, newObj,choice) == -1){
				node newNode = SLCreateNode(newObj,list);
				newNode->next = temp->next;
				temp->next = newNode;
				return;
			}
			temp = temp->next;
		}
		else{
			return;
		}
	}

	node newNode = SLCreateNode(newObj,list);
	temp->next = newNode;
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
