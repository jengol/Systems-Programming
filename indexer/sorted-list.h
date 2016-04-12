#ifndef SORTED_LIST_H
#define SORTED_LIST_H
/*
 * sorted-list.h
 */

#include <stdlib.h>

//======Prototypes for User-Defined Functions==========
//-=-=-=-You do not need to do anything with these definitions-=-=-=-

typedef struct Node* node;
typedef struct SortedList* SortedListPtr;
typedef struct fileData* fileData;

typedef int (*CompareFuncT)(void *,void *,int);
typedef void (*DestructFreq)(void* f);


struct fileData{
	char* filename;
	int frequency;
};

/*
 * Sorted list type that will hold all the data to be sorted.


	our sorted list will have a head node which will point to the list
 */
struct SortedList
{
	node head;
	CompareFuncT cmp;
	DestructFreq dfreq;
};

struct Node{
	void *data;
	struct Node *next;
	int wordcount;
	SortedListPtr fileList;
};


//SLCreateNode creates a node to be inserted into the list

node SLCreateNode(void *data,SortedListPtr list);


/*
 * SLCreate creates a new, empty, 'SortedList'.
 *
 * SLCreate's parameters will be a comparator (cf) and destructor (df) function.
 *   Both the comparator and destructor functions will be defined by the user as per
 *     the prototypes above.
 *   Both functions must be stored in the SortedList struct.
 * 
 * SLCreate must return NULL if it does not succeed, and a non-NULL SortedListPtr
 *   on success.
 */

SortedListPtr SLCreate(CompareFuncT cf, DestructFreq df);


/*
 * SLDestroy destroys a SortedList, freeing all dynamically-allocated memory.
 */
void SLDestroy(SortedListPtr list);


/*
 * SLInsert inserts a given data item 'newObj' into a SortedList while maintaining the
 *   order and uniqueness of list items.
 * 
 * SLInsert should return 1 if 'newObj' is not equal to any other items in the list and
 *   was successfully inserted.
 * SLInsert should return 0 if 'newObj' is equal to an item already in the list or it was
 *   not successfully inserted
 *
 * Data item equality should be tested with the user's comparator function *
 */

int SLInsert(SortedListPtr list, void *newObj,int choice);


/*
 * SLRemove should remove 'newObj' from the SortedList in a manner that
 *   maintains list order.
 *
 * SLRemove must not modify the data item pointed to by 'newObj'.
 *
 * SLRemove should return 1 on success, and 0 on failure.
 */

int SLRemove(SortedListPtr list, void *newObj);

void insertFileData(SortedListPtr list,char* filename,int choice);

void resetList(SortedListPtr list);

void destroyList(SortedListPtr list);

#endif
