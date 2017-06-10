/*
 * 16 March 2017
 * this program was written by
 * jarrod li
 * Collatz Conjecture
 * 3n + 1 Conjecture
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define HALF 0.5


void testPrintWondrous(void) {

    assert
}


/*int printWondrous(int start);

int main(int argc, char *argv[]) {

    int start;
    printf("Enter the starting number: ");
    scanf("%d", &start);

    printWondrous(start);

    return EXIT_SUCCESS;

}

printWondrous(int start) {

    int terms = 1;

    printf("%d ->", start);

    while (start != 1) {

        if (start % 2 == 0) {

            start *= HALF;

            if (start == 1) {

                printf(" %d\n", start);
                terms++;
            } else {

                printf(" %d ->", start);
                terms++;
            }
        } else {

            start = (start * 3) + 1;
            printf(" %d ->", start);
            terms++;
        }
    }

    printf("%d", terms);

    return EXIT_SUCCESS;

}*/


int printWondrous(int start) {

    int terms = 1;

    if (start == 1) {

        printf("%d\n", start);
    } else {

        printf("%d", start);
    }

    while (start != 1) {

        if (start % 2 == 0) {

            start *= HALF;

            if (start == 1) {

                printf(" %d\n", start);
                terms++;
            } else {

                printf(" %d", start);
                terms++;
            }
        } else {

            start = (start * 3) + 1;
            printf(" %d", start);
            terms++;
        }
    }

    return terms;

}
