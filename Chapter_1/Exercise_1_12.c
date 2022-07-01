/*
 * Exercise 1-12. Write a program that prints its input one word per line.
 */

#include <stdio.h>

#define EOF1 '~'
#define BLANK ' '
#define IN 1
#define OUT 0

main()
{
   int c;
   int state = OUT;

   while((c = getchar()) != EOF1)
   {
      if(c == BLANK || c == '\t' || c == '\n')
      {
         if(state == OUT)
         {
            state = IN;
            putchar('\n');
         }
      }
      else
      {
         state = OUT;
         putchar(c);
      }  
   }
 
}
