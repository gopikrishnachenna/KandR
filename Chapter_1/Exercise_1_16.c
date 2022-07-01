/*
 * Exercise 1-16. Revise the main routine of the longest-line program so it will
 * correctly print the length of arbitrarily long input lines, and as much as possible
 * of the text
 */

#include <stdio.h>

#define MAXLINE 1000
#define EOF1 '~'

int mygetline(char a[], int lim);
void copy(char to[], char from[]);

main()
{
   char line[MAXLINE];
   char longest[MAXLINE];
   int len = 0;
   int max = 0;

   while((len = mygetline(line, MAXLINE)) > 0)
      if(len > max)
      {
         max = len;
         copy(longest, line);
      }

   if(max > 0)
   {
      printf("The longest line length is %d\n", max);
      printf("%s\n", longest);
   }

   return 0;
}

int mygetline(char s[], int lim)
{
   int c;
   int i, len;

   for(i = 0, len = 0; ((c = getchar()) != EOF1) && c != '\n'; i++)
   {
      if(i < (lim - 1))
         s[len++] = c;
   }

   if(len == i && i < (lim - 1) && c == '\n')
   {
      s[len++] = c;
      i++;
   }
   s[len] = '\0';

   return i;
}

void copy(char to[], char from[])
{
   int i = 0;

   while((to[i] = from[i]) != '\0')
      i++;
}
