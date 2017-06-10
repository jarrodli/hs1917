#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

/*typedef struct _date {
	int day;
	int month;
	int year;
} date;

int main(int argc, char *argv[]) {

	date birthday = {12, 12, 2000};
	printf("%2d-%2d-%2d", birthday.day, birthday.month, birthday.year);
	return 0;
}*/

typedef struct _complex {

	double real;
	double imaginary;
} complex;

int main(int argc, char *argv[]) {

	return 0;
}

complex sum(complex x, complex y) {
	complex result = {
	result.real = x.real + y.real,
	result.imaginary = x.imaginary + y.imaginary
	};
	return result;
}

complex product(complex x, complex y) {
	complex result;
	result.real = x.real * y.real + a.real
	return result;
}

complex modulus(complex x, complex y) {
	complex result;
	result.real = (a*a + b*b)
	result.imaginary
}

void printComplex(complex x) {

	printf("%")
}

