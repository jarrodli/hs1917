/*
* Test if a point is inside a triangle.
* Julian Saknussemm
*
* Given Three points of a triangle, and another arbitrary point this program
* determines if that point lies inside
* the triangle.
*
* This is determined by satisfying the following rule:
* A point P(x,y) is inside triangle A(x0,y0), B(x1,y1), C(x2,y2)
* if
* P is on the same side of the line AB as C
* P is on the same side of the line BC as A
* and
* P is on the same side of the line AC as B
*
* A special case exits for a vertical line (inf gradient)
* when testing the side of the line
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define UNDER -1
#define ON 0
#define OVER 1

#define TRUE 1
#define FALSE 0

void testTest3(void);
int test1 	(double px, double py, double m, double b, double lx, double ly);
int test2 	(double px, double py, double m, double b);
int test3 	(double x0, double y0, double x1, double y1, double x2, double y2,
			double px, double py);
int test4 	(double x1, double x2, double px, double py, double xx, double y,
		   	double m, double b);


int main (int argc, char* argv[]) {

    testTest3();

    double x0,y0,x1,y1,x2,y2,px;
    double py;

    int numberOfInputs = 0;

    printf("Triangle Vertex A (x,y): " );
	numberOfInputs += scanf("%lf,%lf", &x0,&y0);

    printf("Triangle Vertex  B (x,y): ");
	numberOfInputs += scanf("%lf,%lf", &x1,&y1);

    printf("Triangle Vertex  C (x,y): ");
	numberOfInputs += scanf("%lf,%lf", &x2,&y2);

    printf("Test Point (x,y): "        );
	numberOfInputs += scanf("%lf,%lf", &px,&py);

    if ( numberOfInputs != 8 ) {

        printf("You're stupid and didn't put in the right inputs!\n");

        return 1;
    }

    printf("Point (%.2lf,%.2lf) is ", px, py);

    if (test3(x0, y0, x1, y1, x2, y2, px, py)) {

	    printf("inside");

    } else {

        printf("outside");

    }


    printf(" the triangle.\n");

    return EXIT_SUCCESS;

}


int test1 (double px, double py, double m, double b, double lx, double ly) {
	return test2(px, py, m, b) == test2(lx, ly, m, b);
}


// test if two points lie on same side of a line
int test2 (double px, double py, double m, double b) {

	int position; // variable for position of point

	if( py < m * px + b ) {
		position = UNDER;	// point is under line
	} else if ( py == m * px + b ) {
		position = ON;		// point is on the line
	} else {
		position = OVER;	// point is above the line
	}

	return position;
}


// test cases to test if the triangle test function works
void testTest3(void) {

    assert ((test3(1,0,3,0,2,3,2,2)) == TRUE);
    assert ((test3(1,0,3,0,2,-3,2,-2)) == TRUE);
    assert ((test3(-1,0,-3,0,-2,3,-2,5)) == FALSE);
    assert ((test3(-3,0,3,0,0,2,0,1)) == TRUE);
    assert ((test3(-2,0,-3,0,-2,-3,-5,-6)) == FALSE);

}


// determine gradient and y int
int test3 (double x0, double y0, double x1, double y1, double x2, double y2,
	double px, double py) {

	double m02, m12, b02, b12;
	int isInside;

	double m01 = (y1-y0)/(x1-x0);
	double b01 = (m01 * -x1) + y1;

	// for m = y-y1 / x-x1
    //     b = (m * x1) + y

	m02 = (y2-y0) / (x2-x0);
	m12 = (y2-y1) / (x2-x1);

	b02 = (m02 * -x2) + y2;
	b12 = (m12 * -x2) + y2;

	if ( test4 (x1, x0, px, py, x2, y2, m01, b01) != 0 &&
		 test4 (x1, x2, px, py, x0, y0, m12, b12) != 0 &&
		 test4 (x2, x0, px, py, x1, y1, m02, b02) != 0) {

		isInside = TRUE;
	} else {
		isInside = FALSE;
	}

	return isInside;
}


// test for infinite gradient

int test4 (double x1, double x2, double px, double py, double xx, double y,
	double m, double b) {

	int line;

	if(x1 == x2) {
		line = ((px <= x2) == (xx <= x2));
	} else {
		line = test1(px, py, m, b, xx, y);
	}

	return line;
}
