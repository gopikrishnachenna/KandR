/*
 * Exercise 1-15. Rewrite the temperature conversion program of Section 1.2 to
 * use a function for conversion
 */

#include <stdio.h>

float convtemp(float fahr);

main()
{
   float fahr, Celsius;
   int lower, upper, step;

   lower = 0;
   upper = 300;
   step = 20;

   fahr = lower;
   printf("Fahrenheit - Celsius\n");
   printf("----------   -------\n");
   while(fahr <= upper)
   {
      Celsius = convtemp(fahr);
      printf("%7.0f      %6.1f\n", fahr, Celsius);
      fahr = fahr + step;
   }
}

float convtemp(float fahr)
{
   float Cel;

   Cel = (5.0/9.0) * (fahr - 32.0); 
   return Cel;
}
