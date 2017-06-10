/*
 * arrayoverflow.c
 * Jarrod Li
 * 05 April 2017
 * determines what happens 
 * with various things in the stack
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	int canaryA = 42;
	int testArray[10];
	int canaryB = 99;
	int count = 0;

	while (count < 10) {
		testArray[count] = 0;
		count++;
	}

	int index;

	printf("The memory address of canaryA is: %p\n", &canaryA);
	printf("The memory address of canaryB is: %p\n", &canaryB);
	printf("The memory address of testArray is: %p\n", testArray);

	printf("Enter an array index between 0 and 9\n");
	scanf("%d", &index);
	printf("testArray[%d]=%d, \n", index, testArray[index]);
}