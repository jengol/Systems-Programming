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
  int i = 1;
  void *x;
  printf("argc %d\n", argc);
  //insert all in argv
  for(; i < argc; i++){
    x = (void *)argv[i];
    printf("\nCurrently added: %s\n", argv[i]); 
    SLInsert(s, x);
  }
  Node tmp = s->front;
  int *num;
  i = 1;
  do{
    num = (int *)(tmp->data);
    printf("Print: %d\n",*num);
    tmp = tmp->next;
    i++;
  }while(i < argc);
  //do{
  //}while(i < argc-1);


  printf("Test");
  return 0;
}
