#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void zip (char *s1, char *s2);
int main (void) {
	char s1[] = "hieee";
	char s2[] = "by";
	zip(s1, s2);
	return 0;
}

char *zip (char *s1, char *s2) {
	int totalLength = strlen(s1) + strlen(s2);
	char *result = malloc (totalLength + 1);
	
	int i = 0, j = 0, k = 0;
	
	int larger;
	if (strlen(s1) > strlen(s2)) {
		larger = 0;
	} else if (strlen(s1) < strlen(s2)) {
		larger = 1;
	} else {
		larger = -1;
	}
	
	while (i < totalLength && s1[j] != '\0' && s2[k] != '\0') {
		if (i % 2 == 0) {
			result[i] = s1[j];
			++j;
		} else {
			result[i] = s2[k];
			++k;
		}
		++i;
	}
	
	if (larger == 0) { // if first string is larger
		while (s1[j] != '\0') {
			result[i] = s1[j];
			++j;
			++i;
		}
	} else if (larger == 1) {
		while (s2[k] != '\0') {
			result[i] = s2[k];
			++k;
			++i;
		}
	} else {
	    result[i] = s2[k];
	    ++k;
	    ++i;
	}
	
	result[totalLength] = '\0';
	
	return result;
}