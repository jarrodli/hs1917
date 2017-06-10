/*
 * written by:
 * jarrod li
 * 07 March 2017
 * program that sorts three numbers asc.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int sorting (int a, int b, int c);

int main (int argc, char *argv[]) {

    int a, b, c;

    scanf ("%d %d %d", &a, &b, &c);

    sorting (a, b, c);

    return EXIT_SUCCESS;

}


void testSorting (void) {

    assert (sorting (5, 4, 1) == (1, 4, 5));
    //assert (8, 5, 9 == 5, 8, 9);
    //assert (1, 2, 3 == 1, 2, 3);

}


int sorting (int a, int b, int c) {

    if (a > b && a > c) {
        if (b > c){
            printf("%d\n%d\n%d", c, b, a);
        } else {
            printf("%d\n%d\n%d", b, c, a);
        }

    } else if (b > a && b > c) {
        if (a > c){
            printf("%d\n%d\n%d", c, a, b);
        } else {
            printf("%d\n%d\n%d", a, c, b);
        }

    } else if ( c > a && c > b) {
        if (b > a) {
            printf("%d\n%d\n%d", a, b, c);
        } else {
            printf("%d\n%d\n%d", b, a, c);

        }

    }

    return EXIT_SUCCESS;

}
