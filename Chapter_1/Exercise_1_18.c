/*
 * Exercise 1-18. Write a program to remove trailing blanks and tabs from each
 * line of input, and to delete entirely blank lines.
 */

#include <stdio.h>

#define EOF1 '~'
#define MAXLINE 1000

int mygetline(char a[], int lim);
int removeblank(char from[]);

main()
{
   char line[MAXLINE];
   int len = 0;

   while((len = mygetline(line, MAXLINE)) > 0)
      if(1 == removeblank(line))
      {
         printf("%s",line);
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

int removeblank(char line[])
{
   int i = 0;
   int len = 0;

   if(line[0] == '\n')
      return 0;

   for(i = 0; line[i] != '\0'; i++)
   {
      if(line[i] == '\t' || line[i] == ' ' || line[i] == '\n')
      {
         len++;
      }
      else
      {
         len = 0;
      }
   }

   if(line[i - 1] == '\n')
      line[i - len] = '\n';
   line[i - len + 1] = '\0';

   return 1;
}
