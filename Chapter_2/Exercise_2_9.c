/*
 * Exercise 2-9. In a two's complement number system, x &= (x-1)
 * deletes the rightmost l-bit in x.  Explain why. Use this observation
 * to write a faster version of bitcount.
 */

#include <stdio.h>

#define NO_BITS_INT 32

int bitcount(unsigned x);

main()
{
   unsigned x;
   int z;
   
   printf("Enter the integer - ");
   scanf("%d", &x);

   z = bitcount(x);

   printf("The number of ones in 0x%X %s %d\n", x, (z > 1) ? "are" : "is", z);
}

int bitcount(unsigned x)
{
   int count = 0;

   if(x)
      count++;
   else
      return 0;
   
   while(x &= (x - 1))
      count++;

   return count;
}

