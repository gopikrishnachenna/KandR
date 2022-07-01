/*
 * Exercise 1-17. Write a program to print all input lines that are longer than 80
 * characters.
 */

#include <stdio.h>

#define EOF1 '~'
#define MAXLINE 1000

int mygetline(char a[], int lim);

main()
{
   char line[MAXLINE];
   int len = 0;

   while((len = mygetline(line, MAXLINE)) > 0)
      if(len > 50)
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

