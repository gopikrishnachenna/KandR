/*
 * Exercise 5-1. As written, getint treats a + or - not followed by a digit as a
 * valid representation of zero. Fix it to push such a character back on the input.
 */

#include <stdio.h>
#include "allheader.h"

#define MAXLEN 1000
#define EOF1 '~'

int getint(int *p);

main()
{
   int c;
   int p;

   while((c = getint(&p)) != EOF1 && c != 0)
   {
      printf("%d\n", p);
   }
}

int getint(int *p)
{
   int c, sign;

   while(isspace(c = getch()))
      ;

   if(c != EOF1 && !isdigit(c) && c != '+' && c != '-')
   {
      ungetch(c);
      return 0;
   }

   sign = (c == '-') ? -1 : 1;

   if(c == '-' || c == '+')
   {
      c = getch();
      if(!isdigit(c))
      {
         ungetch(c); /* Should we ungetch the sign too? */
         ungetch((sign == -1) ? '-' : '+');
         return 0;
      }
   } 

   for(*p = 0; isdigit(c); c = getch())
      *p = 10 * *p + c - '0';
   *p *= sign;
   if(c != EOF1)
      ungetch(c);
   return c;
}

