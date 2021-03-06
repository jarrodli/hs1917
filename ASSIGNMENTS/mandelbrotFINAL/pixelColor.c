/*
 * pixelColor.c
 * 10 April 2017
 * Caringbah High School
 * Mirela Jarrod Stan
 * Chooses RGB values for Mandelbrot server
 */
 
#define MAX_ITERATIONS 256

unsigned char stepsToRed (int steps) {

    int valueRed;
    if (steps < 20) {
        valueRed = 0x00;
    } else {
        valueRed = 0xcc;
    }
    if (steps % 3 == 0 ) {
        valueRed = 0xff;
    }
    
    return valueRed;
}
unsigned char stepsToGreen (int steps) {

    int valueGreen;
    if (steps > 200 && steps < 256 ) {
        valueGreen = 0xFF * steps / MAX_ITERATIONS * 2;
    } else if (steps >= MAX_ITERATIONS) {
        valueGreen = 0x55;
    } else if (steps < 100) {
        valueGreen = 0xFF * steps / 30;
    } else {
        valueGreen = 0xff;
    }
    if (steps % 3 == 0 ) {
        valueGreen = 0xff * 23 * steps / MAX_ITERATIONS;
    }
    
    return valueGreen;      
}

unsigned char stepsToBlue (int steps) {

    int valueBlue;
    if (steps > 200 && steps < 256 ) {
        valueBlue = 0xFF * steps / MAX_ITERATIONS * 2;
    } else if (steps >= MAX_ITERATIONS) {
        valueBlue = 0x22;
    } else {
        valueBlue = 0xaa;
    }
    if (steps % 3 == 0 ) {
        valueBlue = 0x00;
    }
    
    return valueBlue;
}