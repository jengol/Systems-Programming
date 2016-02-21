// John Eng and Jamie Liao
#include <stdio.h>
#include "sorted-list.h"

int compare(void *x, void *y){
    int xInt = *((int *)x);
    int yInt = *((int *)y);
    
    return (xInt == yInt) ? 0 : ((xInt>yInt) ? 1 : -1);
}

void destruct(void *x){
    (void) x;
}


int main(int argc, char **argv){
    //Error condition
    if(argv[1] == 0)
        return 0;
    
    //-------------------------------------------------------------------------------------------
    
    
    
    
    //create the SortedListPtr struct + mallocs a struct
    SortedListPtr s = (SortedListPtr)(SLCreate(compare, destruct));

    int i;
    void *x;
    int n;
    
    
    //This is used for testing -- will need to be revised later
    //Array of integers
    int arr[argc-1];
    int index;
    for (index = 0; index < argc-1; index++) {
        arr[index] = atoi(argv[index+1]);
    }
    
    
    printf("argc %d\n", argc);
    //insert all in argv into LL. Sorts as items are inserted O(n) in each pass
    for(i=1; i < argc; i++){
        //Converts string into integer
        x = arr+i-1;
        printf("\nCurrently added: %d\n", n);
        SLInsert(s, x);
    }

    
    
    printf("\n\n");
    //This prints out the data in the list
    Node tmp = s->front;
    int num;
    i = 1;
    do{
        num = *((int *)(tmp->data));
        printf("Print: %d\n",num);
        tmp = tmp->next;
        i++;
    }while(i < argc);
    
    
    
    //-------------------------------------------------------------------------------------------
    // John's Code
    
    
//    SortedListIteratorPtr iter = SLCreateIterator(s);
//    
//    void* ptr;
//    while (1) {
//        ptr = SLGetItem(iter);
//        if (ptr == 0) {
//            break;
//        } else {
//            printf("%d\n",*((int*)ptr));
//        }
//    }
    
    //-------------------------------------------------------------------------------------------
    
    
    
    //Jamie's Code
    //removal of SL and all nodes
//    i = 1;
//    do{
//        SLRemove(s, (void *)argv[i]);
//        i++;
//        printf("\n");
//    }while(i < argc);
//    if(!s->front)
//        printf("YAY\n");
//    SLDestroy(s);
//    if(!s)
//        printf("SortedListPtr successfully deleted");
//    
//    printf("Test");
    return 0;
}