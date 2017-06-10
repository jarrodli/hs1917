/*
 * danish.c
 * written by
 * jarrod li
 * 17 March 2017
 */

#include <stdio.h>
#include <stdlib.h>

#define WIDTH 12
#define HEIGHT 5

void printPixel(int col);
void showDanish(void);

int main(int argc, char *argv[]) {

    showDanish();

    return EXIT_SUCCESS;
}

void showDanish(void) {

    int row = 0;

    while (row < HEIGHT) {

        int col = 0;

        if (row != 2) {
            while (col < WIDTH) {
                printPixel(col);
                col++;
            }
        } else {
            col++;
        }
        row++;
        printf("\n");
    }
}

void printPixel(int col) {

    char pixel;

    if (col == 3) {
        pixel = ' ';
    } else {
        pixel = '*';
    }

    printf("%c", pixel);
}
