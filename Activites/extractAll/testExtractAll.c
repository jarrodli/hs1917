//  Created by Matthew Di Meglio on 17/05/2017.



#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "extractAll.h"

int condition(Link n) {
    return n->value < 5;
}

void printList(List l) {
    if(l->first != NULL) {
        Link curr = l->first;
        while(curr != NULL) {

            printf("%d->", curr->value);
            curr = curr->next;

        }

        printf("X");

    }

}



int main(int argc, const char * argv[]) {

    node f00 = {0, NULL};

    node f08 = {8, &f00};

    node f02 = {2, &f08};

    node f07 = {7, &f02};

    node f03 = {3, &f07};

    list f0 = {&f03};



    node t0m1 = {-1, NULL};

    node t09 = {9, &t0m1};

    list t0 = {&t09};



    printf("Test 0:\nFrom:\n");

    printList(&f0);

    printf("\nTo:\n");

    printList(&t0);

    printf("\nAbout to extract...");



    extractAll(&f0, &t0);



    printf("done.\nFrom:\n");

    printList(&f0);

    printf("\nTo:\n");

    printList(&t0);



    printf("About to test...");



    assert(f0.first == &f07);

    assert(f07.next == &f08);

    assert(f08.next == NULL);



    assert(t0.first == &f03);

    assert(f03.next == &f02);

    assert(f02.next == &f00);

    assert(f00.next == &t09);

    assert(t09.next == &t0m1);

    assert(t0m1.next == NULL);



    printf("\npassed!\n");





    /* Test 1 */

    /* Before:

       FROM->[3]->[7]->[2]->[1]->[8]->[0]->X

       TO->[9]->[-1]->X



       After:

       FROM->[7]->[8]->X

        TO->[3]->[2]->[1]->[0]->[9]->[-1]->X

    */



    node f10 = {0, NULL};

    node f18 = {8, &f10};

    node f11 = {1, &f18};

    node f12 = {2, &f11};

    node f17 = {7, &f12};

    node f13 = {3, &f17};

    list f1 = {&f13};



    node t1m1 = {-1, NULL};

    node t19 = {9, &t1m1};

    list t1 = {&t19};



    printf("\nTest 1:\nFrom:\n");

    printList(&f1);

    printf("\nTo:\n");

    printList(&t1);

    printf("\nAbout to extract...");



    extractAll(&f1, &t1);

    

    printf("done.\nFrom:\n");

    printList(&f1);

    printf("\nTo:\n");

    printList(&t1);



    assert(f1.first == &f17);

    assert(f17.next == &f18);

    assert(f18.next == NULL);



    assert(t1.first == &f13);

    assert(f13.next == &f12);

    assert(f12.next == &f11);

    assert(f11.next == &f10);

    assert(f10.next == &t19);

    assert(t19.next == &t1m1);

    assert(t1m1.next == NULL);



    printf("\npassed!\n");



    list f2 = {NULL};



    node t2m1 = {-1, NULL};

    node t29 = {9, &t2m1};

    list t2 = {&t29};



    printf("\nTest 2:\nFrom:\n");

    printList(&f2);

    printf("\nTo:\n");

    printList(&t2);

    printf("\nAbout to extract...");



    extractAll(&f2, &t2);

    

    printf("done.\nFrom:\n");

    printList(&f2);

    printf("\nTo:\n");

    printList(&t2);



    assert(t2.first == &t29);

    assert(t29.next == &t2m1);

    assert(t2m1.next == NULL);



    printf("\npassed!\n");







    printf("All tests passed!");

    return EXIT_SUCCESS;

}