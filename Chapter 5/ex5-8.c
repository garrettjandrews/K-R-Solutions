#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day) {
    // adding error checking
    if (year < 0) {
        printf("\nError: undefined behavior for negative year.\n");
        return -1;
    }

    if (month < 1 || month > 12) {
        printf("\nError: invalid month selected.\n");
        return -1;
    }

    int i, leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

    // check that day selection is valid
    if (day < 1 || day > daytab[leap][month]) {
        printf("\nError: day selection invalid.\n");
        return -1;
    }

    for (i = 1; i<month; i++) {
        day += daytab[leap][i];
    }
    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

    // check valid year
    if (year < 0) {
        printf("\nError: undefined behavior for negative year.\n");
        return;
    }

    // check valid yearday
    if (leap) {
        if (yearday > 366) {
            printf("Error: there are only 366 days in a leap year.\n");
            return;
        }
    }
    else {
        if (yearday > 365) {
            printf("Error: there are only 365 days in a non-leap year.\n");
            return;
        }
    }

    if (yearday < 1) {
        printf("Error: must enter a positive value for yearday.\n");
        return;
    }

    for (i = 1; yearday > daytab[leap][i]; i++) {
        yearday -= daytab[leap][i];
    }
    *pmonth = i;
    *pday = yearday;
}

int main(void) {
    // todo: print something of interest
}