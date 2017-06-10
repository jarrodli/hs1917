//
//  zipList.h
//  zipListPrac
//
//  Created by Matthew Di Meglio on 25/05/2016.
//  Copyright © 2016 Matthew Di Meglio. All rights reserved.
//

#ifndef zipList_h
#define zipList_h

#include <stdio.h>
#include <stdlib.h>

typedef struct _node *Link;

typedef struct _node {
    int value;
    Link next;
} node;

typedef struct _list *list;

struct _list {
    Link first;
};

list zip(list a, list b);
void printList(list l);
#endif /* zipList_h */

void insertFront(list l, Link n) {
	n->next = l->head;
	l->head = n;
}

Link removeFront(list l) {
	Link n = l->head;
	l->head = n->next;
	return n;
}


int main() {

	struct _list newList= {NULL};
	list reversed = &newList;

	list from = newList();

	while (from->head != NULL) {
		insertFront(reversed, removeFront(from));
	}
}