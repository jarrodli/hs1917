//
// List.c
// hold my balloons
// 

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

typedef struct _node *Node;

typedef struct _list {
	Node first;
} list;

typedef struct _node {
	int value;
	Node next;
} node;

List newList() {
	List l = malloc(sizeof(list));
	l->first = NULL;
	return l;
}

void freeList(List l) {
	if (l != NULL) {
		while (l->first != NULL) {
			removeFromFront(l);
		}
		free(l);
	}
}

void insertAtFront(List l, int value) {
	Node n = malloc(sizeof(node));
	n->value = value;
	n->next = l->first;
	l->first = n;
}

int removeFromFront(List l) {
	Node toKill = l->first;
	int value = toKill->value;
	l->first = toKill->next;
	free(toKill);

	return value;
}

void insertAtEnd(List l, int value) {
	if (l->first == NULL) {
		insertAtFront(l, value);
	} else {
		Node current = l->first;
		while (current->next != NULL) {
			current = current->next;
		}
		Node n = malloc(sizeof(node));
		n->value = value;
		n->next = NULL;
		current->next = n;
	}
}