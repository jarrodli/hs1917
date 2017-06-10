// testpath.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "path.h"

int main(int argc, char *argv[]) {

	// test paths
	char *path1 = "RLLRRLLRL";
	char *path2 = "LL";
	char *path3 = "LRRRRLLR";
	char *path4 = "RLRLRLRLRL";
	char *path5 = "RLRRLLRR";
	char *path6 = "RRLRLLRLRL";
	char *path7 = "LRRLLRRLRLL";
	char *path8 = "R";
	char *path9 = "L";

	printf("testing convert...\n");
	
	path p = "";
	printf("Test 1: %s -> %d\n", p, convert(p));
	assert(convert(p) == 16);
	
	strcpy(p, path1);
	printf("Test 2: %s -> %d\n", p, convert(p));
	assert(convert(p) == 51);
	
	strcpy(p, path2);
	printf("Test 3: %s -> %d\n", p, convert(p));
	assert(convert(p) == -1);
	
	strcpy(p, path3);
	printf("Test 4: %s -> %d\n", p, convert(p));
	assert(convert(p) == 0);

	strcpy(p, path4);
	printf("Test 5: %s -> %d\n", p, convert(p));
	assert(convert(p) == 26);
	printf("all tests passed.\n");

	strcpy(p, path5);
	printf("Test 6: %s -> %d\n", p, convert(p));
	assert(convert(p) == 4);

	strcpy(p, path6);
	printf("Test 7: %s -> %d\n", p, convert(p));
	assert(convert(p) == 6);

	strcpy(p, path7);
	printf("Test 8: %s -> %d\n", p, convert(p));
	assert(convert(p) == 53);

	strcpy(p, path8);
	printf("Test 9: %s -> %d\n", p, convert(p));
	assert(convert(p) == 17);

	strcpy(p, path9);
	printf("Test 10: %s -> %d\n", p, convert(p));
	assert(convert(p) == 27);

	printf("All tests passed!\n");
}