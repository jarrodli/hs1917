/* 
 * frequencyanalysis.c
 * jarrod li
 * 29 March 2017
 * determines frequency
 */

#include <stdio.h>
#include <stdlib.h>

#define SIZE_OF_ALPHABET 26
#define FIRSTU 'A'
#define LASTU 'Z'
#define FIRSTL 'a'
#define LASTL 'z'

int main (int argc, char *argv[]) {

    int frequency[SIZE_OF_ALPHABET];
    int character;
    int clear = 0;
    int charCount = 0;
    int letterCount = 0;
    int count = 0;
    float proportion = 0;
    char letter = 'a';

    // file io

    FILE* txt_file = fopen ("green_eggs_and_ham.txt", "rt");

    // frequency table

    while (clear < SIZE_OF_ALPHABET) {
        frequency[clear] = 0;
        clear++;
    }

    while (1) {
        character = fgetc(txt_file);
        if (character == EOF) {
            break;
        }

        if ('a' <= character && character <= 'z') {
            frequency[character - 'a']++;
        } else if ('A' <= character && character <= 'Z') {
            frequency[character - 'A']++;
        }

        charCount++;
    }

    while (count < 26) {
        letterCount += frequency[count];
        count++;
    }

    printf("\nTotal Characters: %d\n", charCount);
    printf("Total Letters: %d\n\n", letterCount);
    printf("Letter Statistics:\n\n");
    printf("%s  %s  %s\n", "Letter", "Frequency", "Proportion");

    count = 0;

    while (count < 26) {
        proportion = (float) frequency[count] / (float) letterCount * 100;
        printf("%-7c %-10d %.2f%%\n", letter, frequency[count], proportion);
        letter++;
        count++;
    }

    return EXIT_SUCCESS;

}

/*void frequency(int c, int *count);

int count[SIZE_OF_ALPHABET];

int main(int argc, char *argv[]) {

	int charTotal = 0;
    int letterTotal = 0;
    int letterCount = 0;
    int statCount = 0;
    
	//char d = 'a';

	char c;
    
    while (c != EOF) {
        c = getchar();
        frequency(c, count);
        charTotal++;
    }


    while (letterCount < 26) {
    	letterTotal += count[letterCount];
    	letterCount++;
    }

    printf("Total Characters: %d\n", charTotal);
    printf("Total Letters: %d\n", letterTotal);
  	printf("Letter Statistics: \n");

    for (statCount = 0; statCount < 26; statCount++) {
    	printf("%d\n", count[statCount]);
    	//d++;
    	//statCount++;
    }

	return 0;
}

void frequency(int c, int *count) {
	if (c >= FIRSTU && c <= LASTU) {
		count[c - FIRSTU]++;
	}

	if (c >= FIRSTL && c <= LASTL) {
		count[c - FIRSTL]++;
	}
}*/