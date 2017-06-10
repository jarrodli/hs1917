/* 
 * mbFlag.c
 * Jarrod Li
 * 12 April 2017
 * prints the mandelbrotset with '*'
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TRUE 1
#define FALSE 0
#define MAX 256
#define HEIGHT 100
#define WIDTH 125
#define ZOOM 5

typedef struct _complex {
	double real;
	double imag;
} complex;

// Function Prototypes
int escapeSteps (double x, double y);
int inSet (double x, double y);
double square (complex z);
complex sum (complex a, complex b);
complex product (complex a, complex b);
double power (int base, int exponent);

int main (int argc, char *argv[]) {
	int xpoint, ypoint;
	double sxpoint, sypoint, scale;

	assert(inSet(0,1) == TRUE);
    assert(inSet(0,0) == TRUE);
    assert(inSet(-1,0) == TRUE);
    assert(inSet(-1,1) == FALSE);
    assert(inSet(5,0) == FALSE);
    assert(inSet(0,2) == FALSE);
    assert(inSet(3,0) == FALSE);
    assert(inSet(1,0) == FALSE);
    assert(inSet(1,1) == FALSE);

	scale = 1 / power(2, ZOOM);
	ypoint = 0;
	while (ypoint < HEIGHT) {
		xpoint = 0;
		while (xpoint < WIDTH) {
			// center
			sxpoint = -(WIDTH / 2) * scale;
			sypoint = -(WIDTH / 2) * scale;

			// current point
			sxpoint += xpoint * scale;
			sypoint += ypoint * scale;
			if (inSet(sxpoint, sypoint) == TRUE) {
				printf("*");
			} else {
				printf(" ");
			}
			++xpoint;
		}
		printf("\n");
		++ypoint;
	}
	return EXIT_SUCCESS;
}

// determines whether a point is in the mandelbrot set
int inSet (double x, double y) {
	int result;

	if (escapeSteps(x, y) == MAX) {
		result = TRUE;
	} else {
		result = FALSE;
	}

	return result;
}

// determines how many steps until the point escapes the
// mandelbrot set
int escapeSteps (double x, double y) {
    int steps = 0;
    complex z = { 0, 0 };
    complex c = { x, y };
    
    // loop to find when z escapes
    while (steps < MAX && square(z) < 4) {
        z = sum (product (z, z), c);
        ++steps;
    }
    
    return steps;
}

double square (complex z) {
    return z.real * z.real + z.imag * z.imag;
}

// adds two complex numbers
complex sum (complex a, complex b) {
    return (complex) {
        a.real + b.real,
        a.imag + b.imag
    };
}

// multiplys two complex numbers
complex product (complex a, complex b) {
    return (complex) {
        a.real * b.real - a.imag * b.imag,
        a.real * b.imag + a.imag * b.real
    };
}
double power (int base, int exponent) {
	int i = 0;
	double result = 1;
	while (i < exponent) {
		result *= base;
		++i;
	}
	return result;
}