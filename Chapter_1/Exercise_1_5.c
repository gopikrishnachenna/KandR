/*
 * Exercise 1-5. Modify the temperature conversion program to print the table in
 * reverse order, that is, from 300 degrees to 0.
 */

#include <stdio.h>

main()
{
   float fahr, Celsius;
   int lower, upper, step;

   lower = 0;
   upper = 300;
   step = 20;

   fahr = upper;
   printf("Fahrenheit - Celsius\n");
   printf("----------   -------\n");
   while(fahr >= lower)
   {
      Celsius = (5.0/9.0) * (fahr - 32.0);
      printf("%7.0f      %6.1f\n", fahr, Celsius);
      fahr = fahr - step;
   }
}
