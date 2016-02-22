// John Eng and Jamie Liao
#include <stdio.h>
#include "sorted-list.h"

int compare(void *x, void *y){
    int xInt = *((int *)x);
    int yInt = *((int *)y);
    
    return (xInt == yInt) ? 0 : ((xInt>yInt) ? 1 : -1);
}


//Not too sure about this
void destruct(void *x){
    free(x);
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
    int * arr = (int*)malloc((argc-1)*sizeof(int));
    int index;
    for (index = 0; index < argc-1; index++) {
        arr[index] = atoi(argv[index+1]);
    }
    
    
    printf("argc %d\n", argc);
    //insert all in argv into LL. Sorts as items are inserted O(n) in each pass
    for(i=1; i < argc; i++){
        //Converts string into integer
        x = arr+i-1;
        printf("\nCurrently added: %d\n", *((int*)x));
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
    
    
    SortedListIteratorPtr iter = SLCreateIterator(s);
    
    void* item;
    while (1) {
        item = SLGetItem(iter);
        if (item == 0) {
            break;
        } else {
            printf("Iterator: %d\n",*((int*)item));
        }
    }
    
    //-------------------------------------------------------------------------------------------
    
    
    

    //removing all SLNodes
    i = 0;
    do{
        SLRemove(s, (void *)(arr+i));
        i++;
    }while(i < argc-1);
    
    
//    if(s->front==0)
//        printf("Deleted\n");
//    SLDestroy(s);
//    if(s==0)
//        printf("SortedListPtr successfully deleted");
    return 0;
}