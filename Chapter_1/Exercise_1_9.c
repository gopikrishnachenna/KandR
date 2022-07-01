/*
 * Exercise 1-9. Write a program to copy its input to its output, replacing each
 * string of one or more blanks by a single blank
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
      if(c == BLANK)
      {
         if(state == OUT)
         {
            state = IN;
            putchar(c);
         }
      }
      else
      {
         state = OUT;
         putchar(c);
      }  
   }
 
}
