//palindrome.c
//Unofficial Practice Practical Exam
//Created by Michael Simarta
//Jarrod Li

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define FALSE 0
#define TRUE 1

void testCase(void);

int palindrome (char *string);

int main (int argc, char *argv[]) {
    testCase();
    return EXIT_SUCCESS;
}

int palindrome (char *string) {
    int length = strlen(string);
    printf("%d", length);
    char *cpy = malloc(length);
    strcpy(cpy, string);
    int count = 0;
    int lpos = length - 1;
    int state = FALSE;
    while(count < length/2) {
        char temp = string[count];
        cpy[count] = string[lpos - count];
        cpy[lpos] = temp;
        ++count;
    }
    printf("\n%s\n", cpy);
    if(cpy == string) {
        state = TRUE;
    }
    free(cpy);
    return state;
}

void testCase(void) {
    //assert (palindrome("kayak.") == TRUE);
    assert (palindrome("puzzlequest") == FALSE);
    assert (palindrome("is addo odd as i?") == TRUE);
    assert (palindrome("canoe") == FALSE);
    assert (palindrome("eevee") == TRUE);
    assert (palindrome("awesome") == FALSE);
    //ADD MORE TESTS

    printf ("All tests passed, you are Awesome!\n");
}