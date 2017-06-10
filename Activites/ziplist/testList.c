//
//  main.c
//  zipListPrac
//
//  Created by Matthew Di Meglio on 25/05/2016.
//  Copyright © 2016 Matthew Di Meglio. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "zipList.h"

int main(int argc, const char * argv[]) {
    
    
    list l1 = malloc(sizeof(struct _list));
    list l2 = malloc(sizeof(struct _list));
    list zipped;
    
    Link n1 = malloc(sizeof(struct _node));
    Link n2 = malloc(sizeof(struct _node));
    Link n3 = malloc(sizeof(struct _node));
    Link n4 = malloc(sizeof(struct _node));
    Link n5 = malloc(sizeof(struct _node));
    Link n6 = malloc(sizeof(struct _node));
    
    n1->value = 1;
    n2->value = 2;
    n3->value = 3;
    n4->value = 4;
    n5->value = 5;
    n6->value = 6;
    
    
    //test 1
    l1->first = n1;
    n1->next = n2;
    n2->next = n3;
    n3->next = NULL;
    
    l2->first = n4;
    n4->next = n5;
    n5->next = n6;
    n6->next = NULL;
    
    printf("Test 1:\nl1:");
    printList(l1);
    printf("\nl2:");
    printList(l2);
    zipped = zip(l1, l2);
    printf("\nzipped:");
    printList(zipped);
    
    assert(zipped->first == n1);
    assert(zipped->first->next == n4);
    assert(zipped->first->next->next == n2);
    assert(zipped->first->next->next->next == n5);
    assert(zipped->first->next->next->next->next == n3);
    assert(zipped->first->next->next->next->next->next == n6);
    assert(zipped->first->next->next->next->next->next->next == NULL);
    
    //test 2
    
    l1->first = n1;
    n1->next = n2;
    n2->next = NULL;
    
    l2->first = n4;
    n4->next = n5;
    n5->next = n6;
    n6->next = NULL;
    
    printf("\n\nTest 2:\nl1:");
    printList(l1);
    printf("\nl2:");
    printList(l2);
    zipped = zip(l1, l2);
    printf("\nzipped:");
    printList(zipped);
    
    assert(zipped->first == n1);
    assert(zipped->first->next == n4);
    assert(zipped->first->next->next == n2);
    assert(zipped->first->next->next->next == n5);
    assert(zipped->first->next->next->next->next == n6);
    assert(zipped->first->next->next->next->next->next == NULL);
    
    // test 3
    l1->first = n1;
    n1->next = n2;
    n2->next = n3;
    n3->next = NULL;
    
    l2->first = n4;
    n4->next = n5;
    n5->next = NULL;
    
    printf("\n\nTest 3:\nl1:");
    printList(l1);
    printf("\nl2:");
    printList(l2);
    zipped = zip(l1, l2);
    printf("\nzipped:");
    printList(zipped);
    
    assert(zipped->first == n1);
    assert(zipped->first->next == n4);
    assert(zipped->first->next->next == n2);
    assert(zipped->first->next->next->next == n5);
    assert(zipped->first->next->next->next->next == n3);
    assert(zipped->first->next->next->next->next->next == NULL);
    
    //test 4
    l1->first = NULL;
    l2->first = NULL;
    
    printf("\n\nTest 4:\nl1:");
    printList(l1);
    printf("\nl2:");
    printList(l2);
    zipped = zip(l1, l2);
    printf("\nzipped:");
    printList(zipped);
    
    assert(zipped->first == NULL);
    
    
    //test 5
    l1->first = n1;
    n1->next = n2;
    n2->next = n3;
    n3->next = NULL;
    
    l2->first = NULL;
    
    printf("\n\nTest 5:\nl1:");
    printList(l1);
    printf("\nl2:");
    printList(l2);
    zipped = zip(l1, l2);
    printf("\nzipped:");
    printList(zipped);
    
    assert(zipped->first == n1);
    assert(zipped->first->next == n2);
    assert(zipped->first->next->next == n3);
    assert(zipped->first->next->next->next == NULL);
    
    //test 6
    l1->first = NULL;
    
    l2->first = n4;
    n4->next = n5;
    n5->next = n6;
    n6->next = NULL;
    
    printf("\n\nTest 6:\nl1:");
    printList(l1);
    printf("\nl2:");
    printList(l2);
    zipped = zip(l1, l2);
    printf("\nzipped:");
    printList(zipped);
    
    assert(zipped->first == n4);
    assert(zipped->first->next == n5);
    assert(zipped->first->next->next == n6);
    assert(zipped->first->next->next->next == NULL);
    
    
    printf("All tests passed!");
    return EXIT_SUCCESS;
}

void printList(list l) {
	Link cur = l->first;
	while(cur->next != NULL) {
		printf("[%d] -> ", cur->value);
		cur = cur->next; 
	}
	printf("X");
}