typedef struct _node *link; 
 
typedef struct _node {
    int value;
	link next;
} node;

// create an empty list
list newList (void);
// delete the first node
void deleteHead (list l);
// delete the end node
void deleteLast (list l);
// join two lists
// move all the elements from the second list to the end of
// the first list (in order).  this leaves the second list
// empty and all the elements in the first list. 
void concatenate (list to, list from);
// count the number of nodes containing 42
int count42s (list l);