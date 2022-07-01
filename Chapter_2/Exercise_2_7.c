/*
 * Exercise 2-7. Write a function invert(x,p,n) that returns x with the n bits
 * that begin at position p inverted (i.e., I changed into 0 and vice versa), leaving
 * the others unchanged.
 */

#include <stdio.h>

unsigned invert(unsigned x, int p, int n);

main()
{
   unsigned x, z;
   int p = 4, n = 3;
   
   printf("Enter the first integer - ");
   scanf("%d", &x);

   z = invert(x, p, n);

   if(~0 == z)
      printf("Error in conversion.\n");
   else
      printf("First value - 0x%X, Final value - 0x%X\n", x, z);
}

unsigned invert(unsigned x, int p, int n)
{
   unsigned mask;

   if(p < n || p > 32)
      return ~0;

   mask = (~0 << (p + 1)) ^ (~0 << (p + 1 - n));
   x = x ^ mask;

   printf("mask = 0x%X", mask);
   return x;
}

