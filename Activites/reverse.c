/* 
 * reverse.c
 * Jarrod Li
 * 05 April 2017
 * reverses a string
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char *reverse(char *input);

int main(int argc, char *argv[]) {
	char message[100];
	int i = 0;
	while (i < sizeof(message)) {
		message[i] = 0;
		++i;
	}
	printf("String to be reversed:\n");
	fgets(message, sizeof(message), stdin);
	printf("Reversed string: %s", reverse(message));
	return EXIT_SUCCESS;
}

// reverses a string by swapping the ends of a word
// and working in until the two centred letters are reached
// or in an odd case the last letter stays the same
char *reverse(char *message) {

	char *cpy = malloc(strlen(message)); // allocates memory because of segfault
	strcpy(cpy, message);
	int i = 0;
	int len = strlen(cpy);
	int lpos = len - 1; // the last character to be swapped

	// if i == len / 2 then all of the letters in 
	// the string have been swapped
	while(i < len / 2) {

		char temp = cpy[i]; // places the first letter in temp
		cpy[i] = cpy[lpos - i]; 
		cpy[lpos - i] = temp; 
		++i;
	}
	return cpy;
}