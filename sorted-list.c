#include "sorted-list.h"
#include <stdio.h>
//Jamie will do SL functions
//Creates SLPtr struct w/ malloced space and setting struct fields to null. Return SLPtr created 
SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df){
  SortedListPtr s = (SortedListPtr)malloc(sizeof(SortedListPtr));
  if(!s)
    return 0; 
  //creation of initial node and set all fields to null 
  Node tmp = (Node)malloc(sizeof(Node));
  tmp->data = 0;
  tmp->next = 0;
  s->cf = cf;
  s->df = df;
  //setting front to the new node created
  s->front = tmp;
  return s;
}

void SLDestroy(SortedListPtr list){
  if(!list)
    return;
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
  //if there is data is front node, if not adds newobj
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

int SLRemove(SortedListPtr list, void *newObj){
  Node tmp;
  tmp = list->front;
  if(!list || !tmp)
    return 0;

  printf("green\n"); 
  //checks if newobj == front of LL
  if(list->cf(tmp->data, newObj) == 0){ 
    //if only 1 node 
    if(!tmp->next){
      list->front = 0;
      return 1; 
    }
    list->df(tmp->data);
    list->front = tmp->next;
    free(tmp);
    return 1;
  }

  printf("yeller\n"); 
  //loop through until found a match
  do{
    //if matches second node
    if(list->cf(newObj, tmp->next->data) == 0){
      printf("blueeee\n"); 
      list->df(tmp->data);
      free(tmp->next);
      tmp->next = NULL;
      return 1;;
    }
    tmp = tmp->next;
    //return 0 if last node and still no match
    if(!tmp->next)
      return 0;
  }while(list->cf(newObj, tmp->next->data) != 0);

  
  printf("purple\n"); 
  //if node.next == newobj, so DELETE node.next
  if(list->cf(newObj, tmp->next->data) == 0){
    //if DELETED node is second to last

    printf("white\n"); 
    if(tmp->next->next == NULL){
      list->df(tmp->next->data);
      free(tmp->next); 
      tmp->next = NULL;
      return 1;
    }
    //node is has at least 3 before and found a match 
    tmp->next = tmp->next->next;
    list->df(tmp->next->data);
    free(tmp->next);
    return 1;

  }
  return 0;
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
