/*
 * getch and ungetch functions
 */

#include <stdio.h>

#define BUFLEN 1000

int bufp = 0;
int buffer[BUFLEN];

int getch(void)
{
   return (bufp > 0) ? buffer[--bufp] : getchar();
}

void ungetch(int c)
{
   if(bufp >= BUFLEN)
      printf("Buffer overflow.\n");
   else
      buffer[bufp++] = c;
}
