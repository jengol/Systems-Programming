//
//  main.c
//  
//
//  Created by John Eng on 2/17/16.
//
//

#include <stdio.h>
#include "sorted-list.h"



int main(int argc, char **argv){
  //check if at least 1 entry 
  if(argv[1] == 0)
    return 0;

  //create the SortedListPtr struct + mallocs a struct
  SortedListPtr s = (SortedListPtr *)(SLCreate(*(int(CompareFuncT*)(void*, void*)),*(void(DestructFuncT*)(void*))));
  SortedListIteratorPtr *iter = &SLCreateIterator(s);
  
  //tmp is data of each Node that iterator is pointing to
  Node tmp = (Node)malloc(sizeof(Node));
  tmp->data = 5;
  tmp->next = 0;

  printf("%p\n",tmp->data);


  //loops through SL while next is not null
  /*do{
    tmp = &SLGetItem(*iter);




  }while(!s->front->next);
  */

  printf("Test");
  return 0;
}
