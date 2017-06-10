// Dominic He and David Vo
// 18/04/2014
// Functions that return pixel colour for Mandelbrot set

#include <math.h>
#include "pixelColor.h"
#define PI 3.14159265

unsigned char stepsToRed(int steps) {
    int red;
    if (steps == 256) {
        red = 0;
    } else if (steps < 64) {
        red = 128 + 128 * sin(PI * steps / 128);
    } else if (steps <= 128) {
        red = 255;
    } else {
        red = 128 - 128 * cos(PI * steps / 128);
    }
	return red;
}

unsigned char stepsToGreen(int steps) {
    int green;
    if (steps == 256) {
        green = 0;
    } else if (steps < 128) {
        green = 128 - 128 * cos(PI * steps / 128);
    } else if (steps <= 192) {
        green = 255;
    } else {
        green = 128 - 128 * sin(PI * steps / 128);
    }
    return green;
}

unsigned char stepsToBlue(int steps) {
    int blue;
    if (steps == 256 || steps <= 64) {
        blue = 0;
    } else if (steps < 192) {
        blue = 128 - 128 * sin(PI * steps / 128);
    } else {
        blue = 255;
    }
    return blue;
}