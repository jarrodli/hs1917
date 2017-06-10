// a concrete linked list
 
// list is a pointer to a struct - containing the head ptr
// 18 may 2014 tests expanded. includes tests on append to 
// explicitly detect non-null "next" in the appended node.
 
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "list3-core.h"
 
 
// simple unit tests on the list
static void testList (void);
 
int main (int argc, char *argv[])  {
    printf ("Testing list3-core...\n");
    testList();
    printf ("All list3-core tests passed!  You are awesome\n");
 
    return EXIT_SUCCESS;
}
 
 
static void testList (void) {
 
    // create empty lst
    list myList = malloc (sizeof (*myList));
    myList->head = NULL;
    // myList is a struct which has an element head which
    // points to the first node of the list aka the head
 
 
    // simple test on showlist and numItems
    showList (myList);
    assert (numItems (myList) == 0);
 
    // attach one node to the list
    link ptrToNewNode = malloc (sizeof (node));
    assert (ptrToNewNode != NULL); 
    ptrToNewNode->value = 1;
    ptrToNewNode->next = NULL;
 
    myList->head = ptrToNewNode;  
 
    // simple test on showlist and numItems
    showList (myList);
    assert (numItems (myList) == 1);
 
    // attach a second node to the list
    ptrToNewNode = malloc (sizeof (node));
    assert (ptrToNewNode != NULL);  
 
    ptrToNewNode->value = 2;
    ptrToNewNode->next = NULL;
 
    myList->head->next = ptrToNewNode;
 
    showList (myList);
    assert (numItems (myList) == 2);
 
    // insert a node containing 0 at te head, ie before 
    // the 1->2->X list, to produce 0->1->2->X
 
    frontInsert (myList, 0); 
    assert (myList != NULL);
    assert (myList->head != NULL);
    assert (myList->head->value == 0);
    assert (myList->head->next  != NULL);
    assert (myList->head->next->value == 1);
 
    showList (myList);
    assert (numItems (myList) == 3);
 
    // insert at end 
    append (myList, 4);
 
    assert (myList != NULL);
    assert (myList->head != NULL);
    assert (myList->head->next != NULL);
    assert (myList->head->next->next != NULL);
    assert (myList->head->next->next->next != NULL);
    assert (myList->head->next->next->next->value == 4);
    assert (myList->head->next->next->next->next  == NULL);
 
    showList (myList);
    assert (numItems (myList) == 4);
 
    // test lookup
    assert (lookup (myList,0)==0);
    assert (lookup (myList,1)==1);
    assert (lookup (myList,2)==2);
    assert (lookup (myList,3)==4);
}