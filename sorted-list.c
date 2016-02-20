#include "sorted-list.h"
//Jamie will do SL functions
//Creates SLPtr struct w/ malloced space and setting struct fields to null. Return SLPtr created 
SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df){
  SortedListPtr s = (SortedListPtr *)malloc(sizeof(SortedListPtr));
  Node tmp = (Node)malloc(sizeof(Node));
  tmp->data = 0;
  tmp->next = 0;

  s->front = tmp;
  return s;
}

void SLDestroy(SortedListPtr list){
  free(list);
  return;
}

int SLInsert(SortedListPtr list, void *newObj){
 
}

int SlRemove(SortedListPtr list, void *newObj){
 //redirect the next ptr of SortedList to point to .next.next
}


//John will do these :D
SortedListIteratorPtr SLCreateIterator(SortedListPtr list){

}

void SLDestroyIterator(SortedListIteratorPtr iter){
  free(iter);
  return;
}

void *SLNextItem(SortedListIteratorPtr iter){

}

void *SLGetItem(SortedListIteratorPtr iter){
}
