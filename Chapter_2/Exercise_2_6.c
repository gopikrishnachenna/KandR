/*
 * Exercise 2-6. Write a function setbits(x,p,n,y) that returns x with the n
 * bits that begin at position p set to the rightmost n bits of y, leaving the other
 * bits unchanged
 */

#include <stdio.h>

unsigned setbits(unsigned x, int n, int p, unsigned y);

main()
{
   unsigned x, y, z;
   int p = 4, n = 3;
   
   printf("Enter the first integer - ");
   scanf("%d", &x);
   printf("Enter the second integer - ");
   scanf("%d", &y);

   z = setbits(x, p, n, y);

   if(~0 == z)
      printf("Error in conversion.\n");
   else
      printf("First value - 0x%X, Second value - 0x%X, Final value - 0x%X\n", x, y, z);
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{

   unsigned mask;

   if(p < n || p > 32)
      return ~0;

   mask = (~0 << (p + 1)) ^ (~0 << (p + 1 - n));
   x = x & ~mask;
   y = (y & ~(~0 << n)) << (p + 1 - n);
   x = x | y;

   //printf("mask = 0x%X, y = 0x%X\n", mask, y);

   return x;
}

