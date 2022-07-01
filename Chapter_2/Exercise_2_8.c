/*
 * Exercise 2-8. Write a function rightrot(x,n) that returns the value of the
 * integer x rotated to the right by n bit positions.
 */

#include <stdio.h>

#define NO_BITS_INT 32

unsigned rightrot(unsigned x, int n);

main()
{
   unsigned x, z;
   int n = 3;
   
   printf("Enter the first integer - ");
   scanf("%d", &x);

   z = rightrot(x, n);

   printf("First value - 0x%X, Final value - 0x%X\n", x, z);
}

unsigned rightrot(unsigned x, int n)
{
   n = n % NO_BITS_INT;

   return (x >> n);
}

