#include "sorted-list.h"
#include <stdio.h>
//Jamie will do SL functions
//Creates SLPtr struct w/ malloced space and setting struct fields to null. Return SLPtr created 
SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df){
  SortedListPtr s = (SortedListPtr)malloc(sizeof(SortedListPtr));
  if(!s)
    return 0; 
  
  Node tmp = (Node)malloc(sizeof(Node));
  tmp->data = 0;
  tmp->next = 0;

  s->cf = cf;
  s->df = df;

  s->front = tmp;
  return s;
}

void SLDestroy(SortedListPtr list){
  
  free(list);
  return;
}

int SLInsert(SortedListPtr list, void *newObj){
  Node tmp, node;
  if (!list)
    return 0;
  
  tmp = list->front;
  printf("obj: %d\n", *((int *)newObj)  );
  node = (Node)malloc(sizeof(Node));
  printf("oranges\n"); 
  //check if malloc worked
  if(!node)
    return 0;

  printf("apple\n"); 
  //if there is front Node
  if(!tmp->data){
    node->data = newObj;
    node->next = 0;
    list->front = node;
    return 1;
  }
  printf("kumquat\n"); 
  //if newObj > front, put newObj as new front node
  if(list->cf(tmp->data, newObj) <= 0){
    node->next = list->front; 
    node->data = newObj;
    list->front = node;
    return 1;
  }

  printf("watermelon\n"); 
  //while the next node's data exists and newObj's data > node.next
  while(tmp->next && list->cf(tmp->next->data, newObj) == 1){
    tmp = tmp->next;
  }

  printf("bananannaa\n"); 
  //insert into appropriate position once newObjs's data < node.next's data
  node->next = tmp->next;
  node->data = newObj;
  tmp->next = newObj;
  return 1;

}

int SlRemove(SortedListPtr list, void *newObj){
  
}


//John will do these :D
SortedListIteratorPtr SLCreateIterator(SortedListPtr list){
  SortedListIteratorPtr x = (SortedListIteratorPtr)malloc(sizeof(SortedListIteratorPtr));
  if (!x)
    return 0;
  x->s = list;
  return x;
}

void SLDestroyIterator(SortedListIteratorPtr iter){
  free(iter);
  return;
}

void *SLNextItem(SortedListIteratorPtr iter){

}

void *SLGetItem(SortedListIteratorPtr iter){
}
