/*
 * Exercise 1..8. Write a program to count blanks, tabs, and newlines 
 */

#include <stdio.h>

#define EOF1 '~'
//#define TAB '\t'
#define BLANK ' '
//#define NEWLINE '\n'

main()
{
   double nb, nt, nl;
   int c;

   nb = nt = nl = 0;

   while((c = getchar()) != EOF1)
   {
      if(c == '\t')
         nt++;
      else if(c == BLANK)
         nb++;
      else if(c == '\n')
         nl++;
   }

   printf("Number of tabs = %.0f, blanks = %.0f, newlines = %.0f\n", nt, nb, nl);
}
