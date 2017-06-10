//  Created by Matthew Di Meglio on 25/05/2016.

#ifndef zipList_h
#define zipList_h

#include <stdio.h>
#include <stdlib.h>



typedef struct _node *Link;

typedef struct _node {
    int value;
    Link next;
} node;

typedef struct _list *List;

typedef struct _list {
    Link first;
} list;

void extractAll(List from, List to);
int condition(Link l);
void printList(List l);

#endif /* zipList_h */