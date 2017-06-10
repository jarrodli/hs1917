#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define VALUE 42

typedef struct _node *link;

typedef struct _node {
	int value;
	link next;
} node;

typedef struct _list {
	link head;
} *list;

static void testList(void);
void printList(list l);

int main(int argc, char *argv[]) {
	printf("testing functions...");
	testList();
	printf("all tests passed!");
	return EXIT_SUCCESS;
}

list newList(void) {
	list l = malloc(sizeof(struct _list));
	l->head = NULL;
	return l;
}

void deleteHead(list l) {
	link tmp = l->head;
	l->head = tmp->next;
	free(tmp);
}

list deleteLast(list l) {
	link curr = l->head;
	while(curr->next->next != NULL) {
		curr = curr->next;
	}
	curr->next = NULL;
	return l;
}

void concatenate(list to, list from) {
	link curr = to->head;
	if(curr == NULL) {
		to->head = from->head;
	} else {
		while(curr->next != NULL && to->head != NULL) {
			curr = curr->next;
		}
		if(from->head != NULL) {
			curr->next = from->head;
		}
	}
	from->head = NULL;
}

int count42s(list l) {
	int count = 0;
	link curr = l->head;
	while(curr != NULL && curr->value == VALUE) {
		curr = curr->next;
		++count;
	}
	return count;
}

static void testList (void) {
    printf ("testing newList()\n");
    list testList = newList();
    assert (testList->head == NULL);
 
 
    printf ("testing concatenate()\n");
 
    // (3,2) -> (5,0)
    // create a 3 element list
    testList->head = malloc (sizeof (node));
    testList->head->value = 3;
    testList->head->next  = malloc (sizeof (node));
    testList->head->next->value = 1;
    testList->head->next->next  = malloc (sizeof (node));
    testList->head->next->next->value = 4;
    testList->head->next->next->next  = NULL;
 
    // create a two element list
    list testListB = newList();
 
    testListB->head = malloc (sizeof (node));
    testListB->head->value = 1;
    testListB->head->next  = malloc (sizeof (node));
    testListB->head->next->value = 5;
    testListB->head->next->next  = NULL;
 
    concatenate (testList, testListB);
    assert (testListB != NULL);
    assert (testListB->head == NULL);
 
    assert (testList != NULL);
    assert (testList->head != NULL);
    assert (testList->head->value == 3);
    assert (testList->head->next != NULL);
    assert (testList->head->next->value == 1);
    assert (testList->head->next->next != NULL);
    assert (testList->head->next->next->value == 4);
    assert (testList->head->next->next->next != NULL);
    assert (testList->head->next->next->next->value == 1);
    assert (testList->head->next->next->next->next != NULL);
    assert (testList->head->next->next->next->next->value == 5);
    assert (testList->head->next->next->next->next->next == NULL);
 
    // (5,0) -> (5,0)
    concatenate (testList, testListB);
    assert (testListB != NULL);
    assert (testListB->head == NULL);
 
    assert (testList != NULL);
    assert (testList->head != NULL);
    assert (testList->head->value == 3);
    assert (testList->head->next != NULL);
    assert (testList->head->next->value == 1);
    assert (testList->head->next->next != NULL);
    assert (testList->head->next->next->value == 4);
    assert (testList->head->next->next->next != NULL);
    assert (testList->head->next->next->next->value == 1);
    assert (testList->head->next->next->next->next != NULL);
    assert (testList->head->next->next->next->next->value == 5);
    assert (testList->head->next->next->next->next->next == NULL);
 	
    // (0,5) -> (5,0)
    concatenate (testListB, testList);
    assert (testList != NULL);
    assert (testList->head == NULL);
 	
    assert (testListB != NULL);
    assert (testListB->head != NULL);
    assert (testListB->head->value == 3);
    assert (testListB->head->next != NULL);
    assert (testListB->head->next->value == 1);
    assert (testListB->head->next->next != NULL);
    assert (testListB->head->next->next->value == 4);
    assert (testListB->head->next->next->next != NULL);
    assert (testListB->head->next->next->next->value == 1);
    assert (testListB->head->next->next->next->next != NULL);
    assert (testListB->head->next->next->next->next->value == 5);
    assert (testListB->head->next->next->next->next->next == NULL);
}

void printList(list l) {
	link curr = l->head;
	while(curr != NULL) {
		printf("[%d] -> ", curr->value);
		curr = curr->next;
	}
	printf("X\n");
}