/*
 * Exercise 4-7. Write a routine ungets(s) that will push back an entire string
 * onto the input. Should ungets know about buf and bufp, or should it just
 * use ungetch?  
 */

/*
 * I would say that it is best to use ungetch as the least number of 
 * functions given access to external variables it is best.
 */

/*
 * getch and ungetch functions
 */

#include <stdio.h>

#define BUFLEN 1000

int bufp = 0;
char buffer[BUFLEN];

char getch(void)
{
   return (bufp > 0) ? buffer[--bufp] : getchar();
}

void ungetch(char c)
{
   if(bufp >= BUFLEN)
      printf("Buffer overflow.\n");
   else
      buffer[bufp++] = c;
}

void ungets(char s[])
{
   int i;

   for(i = strlen(s) - 1; i >= 0; i--)
      ungetch(s[i]);
}
