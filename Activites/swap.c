/*
 * this program is brought to you by
 * jarrod li
 * on the 17 March 2017
 * takes two numbers in one function and swaps them in another
 * without a return!
 */

#include <stdio.h>
#include <stdlib.h>

void swap(int *first, int *second);

int main(int argc, char *argv[]) {

    int no1, no2;

    printf("Enter two numbers (x, y): ");
    scanf("%d, %d", &no1, &no2);

    int *first = &no1;
    int *second = &no2;

    swap(first, second);

    printf("%d\n", no1);
    printf("%d", no2);

}

void swap(int *first, int *second) {

    int third = 0;

    third = *first;

    *first = *second;

    *second = third;

}
