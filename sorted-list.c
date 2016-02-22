// John Eng and Jamie Liao
#include "sorted-list.h"



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
  //if list is null, return
    if(list==0){
    } else {
        Node ptr = list->front;
        Node prev = 0;
        while (ptr!=0) {
            prev = ptr;
            ptr = ptr->next;
            free(prev);
        }
        free(list);
    }
    return;
}


int SLInsert(SortedListPtr list, void *newObj){
  Node ptr, prev, node;

  if (list==0){
      printf("Within SLInsert: Null List");
      return 0;
  }
    
    
  //-------------------------------------------------------------------------------------------
    
    
  ptr = list->front;
    
  printf("Item inserted: %d\n", *((int*)newObj));
    
 
  //if there is no data in front node, initialize it
  if(ptr->data == 0){
    ptr->data = newObj;
    return 1;
  }
    
    
  //if newObj > front, put newObj as new front node
  if(list->cf(ptr->data, newObj) <= 0){
    node = (Node)malloc(sizeof(Node));
    node->data = newObj;
    node->next = list->front;
    list->front = node;
    return 1;
  }
    
    //Loops through the LL to insert
    //Uses trailing pointer
    while (ptr!=0) {
        
        if (list->cf(newObj,ptr->data)==1) { //If the newObj is greater than next node
            node = (Node)malloc(sizeof(Node));
            node->data = newObj;
            prev->next = node;
            node->next= ptr;
            return 1;
        } else if (list->cf(newObj,ptr->data)==0){ //If newObj already in list
            return 0;
        } else {                                   //newObj is smaller
            prev = ptr;
            ptr = ptr->next;
        }
    }
    
    //At the last Node and newObj < temp
    node = (Node)malloc(sizeof(Node));
    node->data = newObj;
    node->next = 0;
    prev->next = node;
    
    
    return 1;
}


int SLRemove(SortedListPtr list, void *newObj){
    
  //Error conditions
  Node ptr, prev;
  ptr = list->front;
  if(list==0 || ptr==0)
    return 0;
    
 //-----------------------------------------------------------------------------------
    
  //checks if newObj == front of LL
  if(list->cf(ptr->data, newObj) == 0){
      list->front = list->front->next;
      return 1;
  }
  
  //loop through until found a match
    while(ptr!=0){
      if(list->cf(newObj, ptr->data) == 0){
          prev = ptr->next;
          return 1;
      }
      prev = ptr;
      ptr = ptr->next;
  }

  return 0;
}



//John's Code
SortedListIteratorPtr SLCreateIterator(SortedListPtr list){
    //Error condition
    if (list==0) {
        return 0;
    }
    //Dynamically allocate space for iterator
    SortedListIteratorPtr iter = (SortedListIteratorPtr)malloc(sizeof(SortedListIteratorPtr));
    //Set the iterator's values
    iter->slptr = list;
    iter->nptr = list->front; //Sets the Node ptr within list
    
    return iter;
}

void SLDestroyIterator(SortedListIteratorPtr iter){
  free(iter);
  return;
}

/*
    If an item were inserted or deleted, there would not be a change in the iterator
    because the iterator points to the same list.
 
 
 
 */


void *SLNextItem(SortedListIteratorPtr iter){
    
    //If pointing to the front
    if(iter->nptr == iter->slptr->front){
        iter->nptr = iter->nptr->next;
        return iter->slptr->front->data;
    }
    //If null
    if(iter->nptr== 0){
        return 0;
    }
    
    void * ret = iter->nptr->data;
    iter->nptr = iter->nptr->next;
    return ret;
}

void *SLGetItem(SortedListIteratorPtr iter){
    if(iter->nptr == 0){
        return 0;
    }
    void* ret = iter->nptr->data;
    iter->nptr = iter->nptr->next;  //updates the node pointer within the sorted list
    return ret;
}





