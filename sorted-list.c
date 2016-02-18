//Jamie will do SL functions 
SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df){
  SortedListPtr SLptr = (SortedListPtr *)malloc(sizeof(SortedListPtr));


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
