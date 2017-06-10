//
//  zipList.c
//  zipListPrac
//
//  Created by Matthew Di Meglio on 25/05/2016.
//  Copyright © 2016 Matthew Di Meglio. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "zipList.h"
/*
void insertFront(list l, Link n) {
	n->next = l->first;
	l->first = n;
}

Link removeFront(list l) {
	Link n = l->first;
	if(l->first != NULL) {
		l->first = n->next;
	}
	return n;
}

list zip(list a, list b) {
	list zipped = malloc(sizeof(struct _list));
	list l = {NULL};

	while(a->first != NULL || b->first != NULL) {
		
		if(a->first != NULL) {
			insertFront(l, removeFront(a));
		}
		if(b->first != NULL) {
			insertFront(l, removeFront(b));
		}
	}
	while(l->first != NULL) {
		insertFront(zipped, removeFront(l));
	}
	return zipped;
}*/

//  Created by Matthew Di Meglio on 25/05/2016.



#include "zipList.h"



void insertStart(list l, Link node) {

    node->next = l->first;

    l->first = node;

}



Link removeStart(list l) {

    Link toRemove = l->first;

    if (l->first != NULL) {

        l->first = l->first->next;

    }

    return toRemove;

}



list zip(list a, list b) {

    list zipped = malloc(sizeof(struct _list));

    zipped->first = NULL;

    

    struct _list temp;

    temp.first = NULL;

    

    

    while(a->first != NULL || b->first != NULL) {

        if (a->first != NULL) {

            insertStart(&temp, removeStart(a));

        }

        if (b->first != NULL) {

             insertStart(&temp, removeStart(b));

        }

    }

    

    while(tempList->first != NULL) {

        insertStart(zipped, removeStart(&temp));

    }

    

    return zipped;

}

