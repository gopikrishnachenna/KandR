/*
 * Exercise 1-3. Modify the temperature  conversion program  to print a heading
 * above the table.
 */

#include <stdio.h>

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
      Celsius = (5.0/9.0) * (fahr - 32.0);
      printf("%7.0f      %6.1f\n", fahr, Celsius);
      fahr = fahr + step;
   }
}
