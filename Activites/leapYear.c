//
// written by:
// jarrod li
// 02 March 2017
// program to find out if a selected
// year is a leap year or not
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define GREGORIAN_CALENDAR 1582

int main(int argc, char *argv[]){

  int year;

  printf("please enter the year you are interested in\n");

  scanf("%d", &year);

  assert (year >= GREGORIAN_CALENDAR);

  if((year % 400) == 0){
    printf("%d is a leap year!\n", year);
  }

  if((year % 400) != 0){

    if((year % 4) == 0){

      if((year % 100) == 0){

        printf("%d is not a leap year!\n", year);

      } else {

        printf("%d is a leap year!\n", year);

      }

    } else {

      printf("%d is not a leap year!\n", year);

    }

  }

  return EXIT_SUCCESS;

}
