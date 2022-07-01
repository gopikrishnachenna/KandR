/*
 * Exercise 1-10. Write a program to copy its input to its output, replacing each tab by \t, 
 * each backspace by \b, and each backslash by \\. This makes tabs and backspaces visible in an unambiguous way.
 */

#include <stdio.h>

#define EOF1 '~'

main()
{
   int c;

   while((c = getchar()) != EOF1)
   {
      if(c == '\t')
      {
         putchar('\\');
         putchar('t');
      }
      else if(c == '\b')
      {
         putchar('\\');
         putchar('b');
      }
      else if(c == '\\')
      {
         putchar('\\');
         putchar('\\');
      }
      else
         putchar(c);
   }

/* Do not know how to simulate \b character */

}
