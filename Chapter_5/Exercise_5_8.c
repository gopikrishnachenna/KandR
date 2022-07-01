/*
 * Exercise 5-8. There is no error checking in day_of_year
 * or month_day. Remedy this defect.
 */

#include <stdio.h>

int daytab[2][13] = 
{
   {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
   {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int m, int d, int y)
{
   int leap, i;
   int day = 0;

   leap = y % 4 == 0 && y % 100 != 0 || y % 400 == 0;

   if(y <= 0 || m <= 0 || m > 12 || d < 1 || d > daytab[leap][m])
      return -1;

   for(i = 1; i < m; i++)
      day += daytab[leap][i];

   day += d;

   return day;
}

int month_day(int d, int y, int *m, int *day)
{
   int leap, i;

   leap = y % 4 == 0 && y % 100 != 0 || y % 400 == 0;

   if(y <= 0 || d < 0 || d > (leap ? 366 : 365))
      return -1;

   for(i = 0; d > daytab[leap][i]; i++)
      d -= daytab[leap][i];

   *m = i;
   *day = d;
}

main()
{
}
