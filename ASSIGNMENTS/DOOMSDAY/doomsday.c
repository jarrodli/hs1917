/*
 *  doomsday.c
 *  A program to test a function dayOfWeek which determines which
 *  day of the week a particular date falls on.
 *  (only for dates after the start of the Gregorian calendar).
 *
 *  Program stub created by Richard Buckland on 17/03/14
 *  This program by Jarrod Li
 *  Freely licensed under Creative Commons CC-BY-3.0
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define THURSDAY    0
#define FRIDAY      1
#define SATURDAY    2
#define SUNDAY      3
#define MONDAY      4
#define TUESDAY     5
#define WEDNESDAY   6

#define TRUE  1
#define FALSE 0

#define DAYS_PER_WEEK 7

#define JANUARY     1
#define FEBRUARY    2
#define MARCH       3
#define APRIL       4
#define MAY         5
#define JUNE        6
#define JULY        7
#define AUGUST      8
#define SEPTEMBER   9
#define OCTOBER     10
#define NOVEMBER    11
#define DECEMBER    12

#define EVEN_MONTH 2

void testDayOfWeek(void);
int dayOfWeek (int doomsday, int leapYear, int month, int day);
int doomsdayAlgorithm (int day, int doomsdate, int doomsday);

int main (int argc, char *argv[]) {

    testDayOfWeek();

    assert (dayOfWeek (THURSDAY,  FALSE,  4,  4) == THURSDAY);
    assert (dayOfWeek (FRIDAY,    FALSE,  6,  6) == FRIDAY);
    assert (dayOfWeek (MONDAY,    FALSE,  8,  8) == MONDAY);
    assert (dayOfWeek (WEDNESDAY, FALSE, 10, 10) == WEDNESDAY);
    assert (dayOfWeek (FRIDAY,    FALSE, 12, 12) == FRIDAY);
    assert (dayOfWeek (THURSDAY,  FALSE,  9,  5) == THURSDAY);
    assert (dayOfWeek (FRIDAY,    FALSE,  5,  9) == FRIDAY);
    assert (dayOfWeek (SUNDAY,    FALSE,  7, 11) == SUNDAY);
    assert (dayOfWeek (TUESDAY,   FALSE, 11,  7) == TUESDAY);
    assert (dayOfWeek (WEDNESDAY, FALSE,  3,  7) == WEDNESDAY);

    assert (dayOfWeek (THURSDAY,  FALSE,  4,  5) == FRIDAY);
    assert (dayOfWeek (SATURDAY,  FALSE,  6,  5) == FRIDAY);
    assert (dayOfWeek (MONDAY,    FALSE,  8,  9) == TUESDAY);
    assert (dayOfWeek (WEDNESDAY, FALSE, 10,  9) == TUESDAY);
    assert (dayOfWeek (FRIDAY,    FALSE, 12, 20) == SATURDAY);
    assert (dayOfWeek (THURSDAY,  FALSE,  9,  9) == MONDAY);
    assert (dayOfWeek (FRIDAY,    FALSE,  5,  5) == MONDAY);
    assert (dayOfWeek (SUNDAY,    FALSE,  7,  7) == WEDNESDAY);
    assert (dayOfWeek (TUESDAY,   FALSE, 11, 11) == SATURDAY);
    assert (dayOfWeek (THURSDAY,  FALSE,  3, 30) == SATURDAY);
    assert (dayOfWeek (SUNDAY,    FALSE, 9, 8591) == THURSDAY);
    assert (dayOfWeek (TUESDAY,   FALSE,  2,  28) == TUESDAY);
    assert (dayOfWeek (TUESDAY,   FALSE,  2,  27) == MONDAY);
    assert (dayOfWeek (THURSDAY,  FALSE,  1,  3)  == THURSDAY);

    printf ("all tests passed - You are awesome!\n");
    return EXIT_SUCCESS;
}

// class tests for dayOfWeek function

void testDayOfWeek(void) {

    assert (dayOfWeek (WEDNESDAY, FALSE, 8, 31) == FRIDAY);
    assert (dayOfWeek (TUESDAY, TRUE, 8, 18) == FRIDAY);
    assert (dayOfWeek (MONDAY, TRUE, 1, 1) == FRIDAY);
    assert (dayOfWeek (SUNDAY, FALSE, 9, 8591) == THURSDAY);
    assert (dayOfWeek (TUESDAY, TRUE, 2, 28) == MONDAY);
    assert (dayOfWeek (SATURDAY, FALSE, 1,2) == FRIDAY);
    assert (dayOfWeek (SATURDAY, FALSE, 3, 15) == SUNDAY);
    assert (dayOfWeek (WEDNESDAY, FALSE, 12, 19) ==
            dayOfWeek (WEDNESDAY, TRUE, 12, 19) );
    assert (dayOfWeek (FRIDAY, TRUE, 2, 29) == FRIDAY);
    assert (dayOfWeek (MONDAY, TRUE, 1, 9) == SATURDAY);
    assert (dayOfWeek (THURSDAY, TRUE, 2, 29) == THURSDAY);

    printf ("all class tests passed - You are extremely awesome!\n");

}

// given the doomsday for a year, and whether or not it is a
// leap year, this function return the day of the week for any
// given month and day in the year.

int dayOfWeek (int doomsday, int leapYear, int month, int day) {

    int weekday = 0;


    if (month == FEBRUARY) {

        if (leapYear == TRUE) {

            weekday = doomsdayAlgorithm(day, 29, doomsday);
        } else {

            weekday = doomsdayAlgorithm(day, 28, doomsday);
        }
    }

    if (month % EVEN_MONTH == 0 && month != FEBRUARY) {
        weekday = doomsdayAlgorithm(day, month, doomsday);
   }

    if (month % EVEN_MONTH != 0) {
        if (month == JANUARY) {
            if (leapYear == TRUE){

                weekday = doomsdayAlgorithm(day, 4, doomsday);
            } else {

                weekday = doomsdayAlgorithm(day, 3, doomsday);
            }
        }
    }

    if (month == MARCH) {

        weekday = doomsdayAlgorithm(day, 0, doomsday);
    }
    if (month == MAY) {

        weekday = doomsdayAlgorithm(day, 9, doomsday);
    }
    if (month == JULY) {

        weekday = doomsdayAlgorithm(day, 11, doomsday);

    }
    if (month == SEPTEMBER) {

        weekday = doomsdayAlgorithm(day, 5, doomsday);

    }
    if (month == NOVEMBER) {

        weekday = doomsdayAlgorithm(day, 7, doomsday);
    }

    return weekday;
}

// calculates the day of the week determined by the input day and doomsday for
// any given year

int doomsdayAlgorithm (int day, int doomsdate, int doomsday) {

    int daydifference;
    int weekday;

    // the remainder of days between doomsdate and input
    daydifference = (day - doomsdate) % DAYS_PER_WEEK;

    // adds the difference in days to the doomsday to figure out the day of the week
    weekday = (daydifference + doomsday) % 7;

    // if weekday is less than 0 it isn't recognisable by the predetermined
    // definitions of a week, adding 7 will not affect the result
    if (weekday < 0) {

        weekday += 7;
    }

    // if weekday is more than 6 it overflows and isn't recongisable by the
    // definitions of a week, taking away 7 days will not affect the result
    if (weekday > 6) {

        weekday -= 7;
    }

    return weekday;
}
