// extract.c
// funtions and types used to extract x,y,z values from a
// string containing a url of the form
// "http://almondbread.cse.unsw.edu.au:7191/tile_x3.14_y-0.141_z5.bmp"
// initially by richard buckland
// 13 April 2014 - rev 2 - 16 April 2017
// Jarrod 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct _triordinate{
	double x;
	double y;
	long z;
} triordinate;
  
triordinate extract (char *message);

int main (int argc, char *argv[]) {
    
    char *message = "http://almondbread.cse.unsw.edu.au:7191/tile_x3.14_y-0.141_z5.bmp";
    extract (message);
    //printf ("x: %f y: %f z: %d\n", result.x, result.y, result.z);
 
    return EXIT_SUCCESS;
}

triordinate extract (char *message) {
	//triordinate result;
	// copies string to a place allocated in memory
	char *messagecpy = malloc(strlen(message));
    strcpy(messagecpy, message);
 	
 	// delimiters
 	// seperates x and y values
 	const char d[4] = "_xy";
 	// seperates z value
 	const char d2[3] = "z.";

 	char *token;
 	char x[30];
 	char y[30];
 	char z[30];

 	// seperates x, y, z values from the main string
 	token = strtok(messagecpy, d);
 	token = strtok(NULL, d);
 	strcpy(x, token);
 	token = strtok(NULL, d);
 	strcpy(y, token);
 	token = strtok(NULL, d2);
 	strcpy(z, token);

 	printf("%s\n", x);
 	printf("%s\n", y);
 	printf("%s\n", z);

 	triordinate result {
 	result.x = myAtoD(x);
 	result.y = myAtoD(y);
 	result.z = myAtoL(z);
 	} 
 	return result;
 	
} 

double myAtoD (char *message) {

}
 
long myAtoL (char *message) {

}