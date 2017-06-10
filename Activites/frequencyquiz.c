/* 
 * frequencyquiz.c
 * jarrod li
 * 03 April 2017
 * completes the frequency quiz
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
    int vowel[5] = {'a', 'e', 'i', 'o', 'u'};
    int upper = 0;
    int lower = 0;
    int character;
    int clear = 0;
    int bytes = 0;
    int lf = 0;
    int space = 0;
    int letterCount = 0;
    int count = 0;
    //int vcount = 0;
    int vfrequency = 0;
    float proportion = 0;
    float vproportion = 0;
    char letter = 'a';

    // file io

    FILE* txt_file = fopen("hamlet-lf.txt", "rt");

    // frequency table

    while (clear < 26) {
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
            lower++;
        } else if ('A' <= character && character <= 'Z') {
            frequency[character - 'A']++;
            upper++;
        }
        if (character == 10) {
            lf++;
        }
        if (character == 32) {
            space++;
        }
        count = 0;
        while (count < 5) {
            if (character == vowel[count]) {
                vfrequency++;
            }
            count++;
        }
        bytes++;
    } 

    count = 0;

    while (count < 26) {
        letterCount += frequency[count];
        count++;
    }

    printf("there are %d letters\n", upper + lower);
    printf("%d upper case letters & %d lower case letters\n", upper, lower);
    printf("File Size: %d bytes\n", bytes);
    printf("lf characters: %d\n", lf);  
    printf("there are %d spaces\n", space);

    count = 0;

    while (count < 26) {
        proportion = (float) frequency[count] / (float) letterCount * 100;
        printf("%-7c %-10d %.5f%%\n", letter, frequency[count], proportion);
        letter++;
        count++;
    }

    printf("the number of vowels is: %d\n", vfrequency);

    vproportion = (float) vfrequency / (float) letterCount * 100;
    printf("percentage proportion of vowels to characters is : %0.1lf\n", vproportion);
    
    return EXIT_SUCCESS;

}