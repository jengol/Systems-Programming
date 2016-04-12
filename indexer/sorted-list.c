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
	newNode->wordcount = 0;
	newNode->fileList = SLCreate(list->cmp,list->dfreq);
	return newNode;
}

int SLInsert(SortedListPtr list,void *newObj,int choice){

	//tested
	if (list->head == NULL){
		node newNode = SLCreateNode(newObj,list);
		newNode->wordcount++;
		list->head = newNode;
		return 1;
	}
	//tested
	if (list->cmp(list->head->data, newObj,choice) == -1){
		node newNode = SLCreateNode(newObj,list);
		newNode->wordcount++;
		newNode->next = list->head;
		list->head = newNode;
		return 1;
	}
	//tested
	if((list->cmp(list->head->data, newObj,choice) == 1) && list->head->next == NULL){
		node newNode = SLCreateNode(newObj,list);
		newNode->wordcount++;
		newNode->next = list->head->next;
		list->head->next = newNode;
		return 1;
	}
	//tested
	if(list->cmp(list->head->data, newObj,choice) == 0){
		list->head->wordcount++;
		return 0;
	}

	node temp = list->head;

	while(temp->next != NULL){
		if(list->cmp(temp->next->data, newObj,choice)!= 0){
			if(list->cmp(temp->next->data, newObj,choice) == -1){
				node newNode = SLCreateNode(newObj,list);
				newNode->wordcount++;
				newNode->next = temp->next;
				temp->next = newNode;
				return 1;
			}
			temp = temp->next;
		}
		else{return 0;}
	}

	node newNode = SLCreateNode(newObj,list);
	newNode->wordcount++;
	temp->next = newNode;
	return 1;	

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
