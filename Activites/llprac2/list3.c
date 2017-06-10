//Written by Michael Simarta
//With the help of Bernice Chen
//List3.c file that implements all functions declared in List3.h
//implement the insert() functions here

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "List3.h"

typedef struct _node {
  int value;
  Node next;
  Node prev;
} node;

typedef struct _list {
  Node head;
  Node tail;
} list;

void insertFront(List l, Node n) {
	n->next = l->head;
	l->head = n;
}

void removeHead(List l) {
	Node n = l->head;
	l->head = n->next;
	return n;
}

void insertInto(List l, Node currentNode, Node insertNode) {
   currentNode->next = insertNode->next;
   currentnode->next = insertNode;
}

//TODO
//Read List3.h to help you look at the hints
//insert nodes into the list so it is in increasing order from head to tail
//and decreasing order from tail to head (You need to uncomment the commented test lines in testList3.c)

void insert(List l, int value) {
	Node n = newNode(value);
   while(l->head != NULL) {
      if(n->head->value == NULL) {
         n->head = l->head;
         n->head->previous = NULL;
         n->head->next = NULL;
      } else if (l->head->value < n->head->value) {
         insertFront(n, removeHead(l));
      } else if (l->head->value > n->head->value) {
         Node cur = n->head;
         while(l->head->value < cur->value) {
            cur = cur->next;
         }
         insertInto(n, cur, removeHead(l));
      }
   }
   l->head = n->head;
   free(n);
}

//returns a new list of length 0
List newList() {
 List l = malloc(sizeof(list));
 assert ( l!=NULL );
 l->head = NULL;
 l->tail = NULL;
 return l;
}

//frees everything malloced for the list
void destroy(List l) {
 Node curNode = l->head;
 Node prevNode = NULL;
 
 while (curNode != NULL) {
   prevNode = curNode;
   curNode = prevNode->next;
   free(prevNode);
 }
 
 free(l);
}

Node newNode (int value) {
 Node n = malloc(sizeof(node));
 n->value = value;
 n->next = NULL;
 n->prev = NULL;
 return n;
}

//appends a node of value to the end of the list (only goes forward)
void append(List l, int value) {
 Node newNode = malloc(sizeof(node));
 newNode->value = value;
 newNode->next = NULL;
 Node curNode = l->head;
 if ( curNode==NULL ) {
  l->head = newNode;
} else {
  while ( curNode->next!=NULL ) {
   curNode = curNode->next;
 }
 curNode->next = newNode;
}
}

//returns the int value of the node at index
//assumes input index is within range of the list's length
int getValue(List l, int index) {

 Node curNode = l->head;
 assert (curNode!=NULL);
 int counter = 0;
 while (counter<index) {
  curNode = curNode->next;
  counter++;
}
return curNode->value;
}

int getValueReverse(List l, int index) {

 Node curNode = l->tail;
 assert (curNode!=NULL);
 int counter = 0;
 while (counter<index) {
  curNode = curNode->prev;
  counter++;
}
return curNode->value;
}

//print List from head to tail
void printList(List l) {
 Node curNode = l->head;
 printf("[HEAD]->");
 while (curNode!=NULL) {
  printf ("[%d]->", curNode->value);
  curNode = curNode->next;
}
printf("[NULL]\n");
}

//print List from tail to head
void printListReverse(List l) {
 Node curNode = l->tail;
 printf("[TAIL]->");
 while (curNode!=NULL) {
  printf ("[%d]->", curNode->value);
  curNode = curNode->prev;
}
printf("[NULL]\n");
}