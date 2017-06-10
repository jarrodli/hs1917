#include <stdio.h>
struct point {
		int x;
		int y;
		int z;
};
int main (void) {
	
	struct point array[50];
	array[0].x = 1;
	array[1].x = 2;
	printf ("%i\n", array[0].x);
	printf ("%i\n", array[1].x);

	return 0;
}