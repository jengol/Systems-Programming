#include "sorted-list.h"
//Jamie will do SL functions
//Creates SLPtr struct w/ malloced space and setting struct fields to null. Return SLPtr created 
SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df){
  SortedListPtr s = (SortedListPtr)malloc(sizeof(SortedListPtr));
  if(!s)
    return 0; 
  
  Node tmp = (Node)malloc(sizeof(Node));
  tmp->data = 0;
  tmp->next = 0;

  s->front = &tmp;
  return s;
}

void SLDestroy(SortedListPtr list){
  free(list);
  return;
}

int SLInsert(SortedListPtr list, void *newObj){
  if (!list)
    return 0;

  Node tmp = list->front;
  //if newObj > front, put newObj as new front node
  if(list->cd(tmp->data, newObj) <= 0){
    Node node = (Node)malloc(sizeof(Node));
    node->next = list->front; 
    node->data = newObj;
    list->front = node;
    return 1;
  }

  //while the next node's data exists and newObj's data > node.next
  while(tmp->next && list->cf(tmp->next-data, newObj) == 1){
    tmp = tmp->next;
  }

  //insert into appropriate position once newObjs's data < node.next's data
  Node node = (Node)malloc(sizeof(Node));
  node->next = tmp->next;
  node->data = newObj;
  tmp->next = newObj;
  return 1;

}

int SlRemove(SortedListPtr list, void *newObj){
 //redirect the next ptr of SortedList to point to .next.next
}


//John will do these :D
SortedListIteratorPtr SLCreateIterator(SortedListPtr list){
  SortedListIteratorPtr x = (SortedListIteratorPtr)malloc(sizeof(SortedListIteratorPtr));
  if (!x)
    return 0;
  x->ptr = list;
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
