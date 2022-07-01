/*
 * Exercise 5-2. Write getfloat, the floating-point analog of getint.
 * What type does getfloat return as its function value?
 */

#include <stdio.h>
#include "allheader.h"

#define MAXLEN 1000
#define EOF1 '~'

int getfloat(float *p);

main()
{
   int c;
   float p;

   while((c = getint(&p)) != EOF1 && c != 0)
   {
      printf("%g\n", p);
   }
}

int getint(float *p)
{
   int c, sign;
   int power;

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

   for(*p = 0.0; isdigit(c); c = getch())
      *p = 10.0 * *p + c - '0';

   if(c == '.')
      c = getch();

   for(power = 1; isdigit(c); c = getch())
   {
      *p = 10.0 * *p + c - '0';
      power *= 10;
   }

   //printf("%f %d\n", *p, power);

   *p = *p / (float)power;
   //printf("%f %d\n", *p, power);
   *p *= sign;
   if(c != EOF1)
      ungetch(c);
   return c;
}

