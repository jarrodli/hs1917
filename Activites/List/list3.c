// list3.c
// jarrod li

#include <stdio.h>
#include <stdlib.h>
#include "list3-core.h"

// new node
link newNode (void) {
	link l = malloc(sizeof(node));
	l->next = NULL;
	return l;
}

// print out a list
void showList (list listToPrint) {
	link cur = listToPrint->head;
	while(cur != NULL) {
		printf("%d", cur->value);
		cur = cur->next;
	}
}
 
// inset item at the front of the list
void frontInsert (list l, int item) {
	link nl = newNode();
	nl->value = item;
	nl->next = l->head;
	l->head = nl;
}
 
// count the number of items in the list
int numItems (list l) {
	int count = 0;
	link cur = l->head;
	while(cur != NULL) {
		++count;
		cur = cur->next;
	}
	return count;
}
 
// insert at end of list
void append (list l, int value) {
	link nl = newNode();
	link cur = l->head;
	while(cur->next != NULL) {
		cur = cur->next;
	}
	cur->next = nl;	
	nl->value = value;
}
 
// find the value stored at position i
// i MUST be a valid position in the list
// dont call this on positions outside the list
int lookup (list l, int position) {
	int i = 0;
	link cur = l->head;
	while(i < position) {
		cur = cur->next;
		++i;
	}
	printf("\n%d\n", cur->value);
	return cur->value;
}