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
        free(list);
    }
    return;
}




int SLInsert(SortedListPtr list, void *newObj){
  Node tmp, node;

  if (list==0){
      printf("Within SLInsert: Null List");
      return 0;
  }
    
    
  //-------------------------------------------------------------------------------------------
    
    
  tmp = list->front;
    
  printf("Item inserted: %d\n", *((int*)newObj));
  //Dynamically allocated Node
  node = (Node)malloc(sizeof(Node));
    
 
  //if there is no data in front node, initialize it
  if(tmp->data == 0){
    tmp->data = newObj;
    return 1;
  }
    
    
  //if newObj > front, put newObj as new front node
  if(list->cf(tmp->data, newObj) <= 0){
    node->next = list->front; 
    node->data = newObj;
    list->front = node;
    return 1;
  }

    
    
    
    
    
    
    
    
    
    
    

  //while the next node's data exists and newObj's data > node.next
  while(tmp->next && list->cf(tmp->next->data, newObj) == 1){
    tmp = tmp->next;
  }


  //insert into appropriate position once newObjs's data < node.next's data
  node->next = tmp->next;
  node->data = newObj;
  tmp->next = node;
  return 1;

}










//Haven't looked at this yet

int SLRemove(SortedListPtr list, void *newObj){
  Node tmp;
  tmp = list->front;
  if(!list || !tmp)
    return 0;

 
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


  //loop through until found a match
  do{
    //if matches second node
    if(list->cf(newObj, tmp->next->data) == 0){

      list->df(tmp->data);
      free(tmp->next);
      tmp->next = 0;
      return 1;;
    }
    tmp = tmp->next;
    //return 0 if last node and still no match
    if(!tmp->next)
      return 0;
  }while(list->cf(newObj, tmp->next->data) != 0);

  

  //if node.next == newobj, so DELETE node.next
  if(list->cf(newObj, tmp->next->data) == 0){
    //if DELETED node is second to last


    if(tmp->next->next == 0){
      list->df(tmp->next->data);
      free(tmp->next); 
      tmp->next = 0;
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

void *SLNextItem(SortedListIteratorPtr iter){
    //method not complete
    if(iter->nptr->next == 0){
        return 0;
    }
    return 0;
}

void *SLGetItem(SortedListIteratorPtr iter){
    if(iter->nptr == 0){
        return 0;
    }
    
    void* ret = iter->nptr->data;
    iter->nptr = iter->nptr->next;  //updates the node pointer within the sorted list
    return ret;
}





