/*
 * rot13.c
 * written by
 * jarrod li and mirelacle
 * 17 March 2017
 * it's a secret
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <assert.h>

 #define CIPHER 13
 #define OVERFLOW 26

 #define FIRST_LOWER 97
 #define LAST_LOWER 122
 #define FIRST_UPPER 65
 #define LAST_UPPER 90

int determineOverflow (int ascii, int original);
void testEncode (void);
int isPermitted (int letter);
char encode (char letter);

int main (int argc, char *argv[]) {

    testEncode();

    char letter;

    scanf("%c", &letter);

    printf("new char: %c", encode(letter));

    return EXIT_SUCCESS;
}

// function to test encode
void testEncode (void){

    assert(encode('h') == 'u');
    assert(encode('H') == 'U');
    assert(encode('z') == 'm');
    assert(encode('Z') == 'M');
    assert(encode( 7 ) ==  7 );

    printf("> passed all tests\n");

}

// encodes the data by adding 13 to the ascii value
char encode (char letter) {

    char cipherText;
    int ascii = letter;
    int original = letter;

    if (isPermitted(letter)) {

        ascii += CIPHER;
        ascii = determineOverflow(ascii, original);
        cipherText = ascii;

    } else {
        cipherText = letter;
    }
    return cipherText;
}

// determines if the input is a permitted character type
int isPermitted (int letter) {

    return (((letter >= FIRST_UPPER) && (letter <= LAST_UPPER)) ||
            ((letter >= FIRST_LOWER) && (letter <= LAST_LOWER)));

}

// determines if the letter needs to be wrapped around to a
int determineOverflow (int ascii, int original) {

    int encoded = ascii;

    if (encoded > 122) {
        encoded -= OVERFLOW;
    } else if (encoded > 90 && original < 91) {
        encoded -= OVERFLOW;
    }

    return encoded;
}
