//
// written by:
// jarrod li
// 04 March 2017
// program to return 1 if leap year
// and 0 if not a leap year
// test cases:
// 1. 4000 - yes
// 2. 4004 - yes
// 3. 1999 - no
// 4. 1900 - no
// 5. 2000 - yes
// 6. 1904 - yes
// 7. 1901 - no
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define GREGORIAN_CALENDAR 1582
#define True               1
#define False              0

int isLeapYear(int year);

int main(int argc, char *argv[]){

  int year;

  printf("enter the year you wish to test:\n");

  scanf("%d", &year);

  if(isLeapYear(year)) {

    printf("is a leap year\n");

  } else {

    printf("is not a leap year!\n");

  }

  return EXIT_SUCCESS;

}

int isLeapYear(int year){

  int leapYear = False;

  assert ( year >= GREGORIAN_CALENDAR );

  if((year % 400) == 0){

    leapYear = True;

  }

  if((year % 400) != 0){

    if((year % 4) == 0){

      if((year % 100) != 0){

        leapYear = False;

      }

    }

  }

  return leapYear;

}
