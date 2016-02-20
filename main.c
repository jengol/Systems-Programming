//
//  main.c
//  
//
//  Created by John Eng on 2/17/16.
//
//

#include <stdio.h>
#include "sorted-list.h"

int compare(void *x, void *y){
  int xInt = *((int *)x);
  int yInt = *((int *)y);

  if(xInt == yInt)
    return 0;
  if(xInt > yInt)
    return 1;
  return -1;
}

void destruct(void *x){
  (void) x;
}


int main(int argc, char **argv){
  //check if at least 1 entry 
  if(argv[1] == 0)
    return 0;
  //create the SortedListPtr struct + mallocs a struct
  SortedListPtr s = (SortedListPtr)(SLCreate(compare, destruct));
  SortedListIteratorPtr iter = SLCreateIterator(s);
  int i = 0;
  void *x;
  printf("argc %d\n", argc); 
  do{
    x = (void *)argv[i];
    //tmp is data of each Node that iterator is pointing to
    Node tmp = (Node)malloc(sizeof(Node));
    if(!tmp)
      return 0;
    tmp->data = x; //sets the data of node to be equal to argv[i]
    tmp->next = 0;
    //printf("%d\n",*((int *)tmp->data));
    printf("hello\n"); 

    i++;
  }while(i < argc-1);


  printf("Test");
  return 0;
}
