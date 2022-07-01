/*
 * Exercise 1-4. Write a program to print the corresponding Celsius to Fahrenheit
 * table.
 */

#include <stdio.h>

main()
{
   float fahr, Cel;
   int lower, upper, step;

   lower = 0;
   upper = 300;
   step = 20;

   Cel = lower;
   printf("Celsius - Farenheit\n");
   printf("-------   ---------\n");
   while(Cel <= upper)
   {
      fahr = ((9.0/5.0) * Cel) + 32;
      printf("%5.0f      %6.1f\n", Cel, fahr);
      Cel = Cel + step;
   }
}
