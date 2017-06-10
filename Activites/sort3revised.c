/*
 * sort3revised.c
 * jarrod li
 * rev 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _sorted {
	int lowestNum;
	int middleNum;
	int highestNum;
} sorted;

int sorting(int a, int b, int c);

int main(int argc, char *argv[]) {

    int a, b, c;
    sorted numbers;

    scanf("%d %d %d", &a, &b, &c);
    sorting(a, b, c);
    printf("%d, %d, %d", sorted.lowestNum, sorted.middleNum, sorted.highestNum);

    return EXIT_SUCCESS;

}


void testSorting(void) {

    assert (sorting (5, 4, 1) == (1, 4, 5));
    //assert (8, 5, 9 == 5, 8, 9);
    //assert (1, 2, 3 == 1, 2, 3);

}


int sorting(int a, int b, int c) {

    if (a > b && a > c) {
        if (b > c){
            sorted numbers = {c, b, a};
        } else {
            sorted numbers = {b, c, a};
        }

    } else if (b > a && b > c) {
        if (a > c){
            sorted numbers = {c, a, b};
        } else {
            sorted numbers = {a, c, b};
        }

    } else if (c > a && c > b) {
        if (b > a) {
            sorted numbers = {a, b, c};
        } else {
            sorted numbers = {b, a, c};
        }

    }
    return sorted;
}
