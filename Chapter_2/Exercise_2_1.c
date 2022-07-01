/*
 * Exercise 2-1. Write a program to determine the ranges of char, short, int,
 * and long variables, both signed and unsigned, by printing  appropriate
 * values from standard headers and by direct computation. Harder  if you com-
 * pute them:  determine the ranges of the various floating-point types.
 */

#include <stdio.h>
#include <limits.h>

void printlen(void);
void calclen(void);

main()
{
   printf("*****************************************************************************************************\n"); 
   printlen();
   printf("*****************************************************************************************************\n"); 
   calclen();
   printf("*****************************************************************************************************\n"); 
}

void printlen(void)
{
   printf("Character \t\t\tmin = %25d, max = %25d\n", CHAR_MIN, CHAR_MAX);
   printf("Signed Character \t\tmin = %25d, max = %25d\n", SCHAR_MIN, SCHAR_MAX);
   printf("Unsigned Character \t\tmin = %25d, max = %25d\n", 0, UCHAR_MAX);
   printf("Signed Integer \t\t\tmin = %25d, max = %25d\n", INT_MIN, INT_MAX);
   printf("Unsigned Integer \t\tmin = %25d, max = %25u\n", 0, UINT_MAX);
   printf("Signed Short \t\t\tmin = %25d, max = %25d\n", SHRT_MIN, SHRT_MAX);
   printf("Unsigned Short \t\t\tmin = %25d, max = %25d\n", 0, USHRT_MAX);
   printf("Signed Long \t\t\tmin = %25ld, max = %25lu\n", LONG_MIN, LONG_MAX);
   printf("Unsigned Long \t\t\tmin = %25ld, max = %25lu\n", 0, ULONG_MAX);
}

void calclen(void)
{
   char char_max = 1, char_min, char_med = 2;
   int int_max = 1, int_min, int_med = 2;
   short shrt_max = 1, shrt_min, shrt_med = 2;
   long long_max = 1, long_min, long_med = 2;
   unsigned char uchar_max = ~0;
   unsigned int uint_max = ~0;
   unsigned short ushrt_max = ~0;
   unsigned long ulong_max = ~0;

   while(char_med > char_max)
   {
      char_max = char_med;
      char_med = char_max * 2;
   }
   char_max = char_med - 1;
   char_min = char_max * -1 - 1;
   while(shrt_med > shrt_max)
   {
      shrt_max = shrt_med;
      shrt_med = shrt_max * 2;
   }
   shrt_max = shrt_med - 1;
   shrt_min = shrt_max * -1 - 1;
   while(long_med > long_max)
   {
      long_max = long_med;
      long_med = long_max * 2;
   }
   long_max = long_med - 1;
   long_min = long_max * -1 - 1;
   while(int_med > int_max)
   {
      int_max = int_med;
      int_med = int_max * 2;
   }
   int_max = int_med - 1;
   int_min = int_max * -1 - 1;

   printf("Character \t\t\tmin = %25d, max = %25d\n", char_min, char_max);
   printf("Signed Character \t\tmin = %25d, max = %25d\n", char_min, char_max);
   printf("Unsigned Character \t\tmin = %25d, max = %25d\n", 0, uchar_max);
   printf("Signed Integer \t\t\tmin = %25d, max = %25d\n", int_min, int_max);
   printf("Unsigned Integer \t\tmin = %25d, max = %25u\n", 0, uint_max);
   printf("Signed Short \t\t\tmin = %25d, max = %25d\n", shrt_min, shrt_max);
   printf("Unsigned Short \t\t\tmin = %25d, max = %25d\n", 0, ushrt_max);
   printf("Signed Long \t\t\tmin = %25ld, max = %25lu\n", long_min, long_max);
   printf("Unsigned Long \t\t\tmin = %25ld, max = %25lu\n", 0, ulong_max);


}
