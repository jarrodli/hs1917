//Written by Michael Simarta
//With the help of Bernice Chen
//header file for a Linked List structure
//contains functions that can be implemented on a Linked List
 
typedef struct _node* Node;
typedef struct _list* List;
 
 
//returns a new list of length 0
List newList();
//frees everything malloced for the list
void destroy(List l);
//appends a node of value to the end of the list
void append(List l, int value);
//returns the int value of the node at index
//assumes input index is within range of the list's length
int getValue(List l, int index);

//find the median of the list
//First, you can assume that the sorted list and has an odd number of elements.
//
//Then, the list is still sorted but may have even or odd number of elements.
int median(List l);