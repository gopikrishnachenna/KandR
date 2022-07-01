/*
 * Exercise 4-8. Suppose that there will never be more than one character of
 * pushback. Modify getch and ungetch accordingly.
 */

/*
 * getch and ungetch functions
 */

#include <stdio.h>

char buf = '\0';

char getch(void)
{
   char result;

   if(buf != '\0')
   {
      result = buf;
      buf = '\0';
   }
   else
      result = getchar();

   return result;
}

void ungetch(char c)
{
   buf = c;
}
