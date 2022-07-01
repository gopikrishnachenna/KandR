/*
 * Exercise 5-4. Write the function strend (s, t), which returns 1 if the string
 * t occurs at the end of the string s, and zero otherwise.
 */

#include <stdio.h>
#include "allheader.h"

#define MAXLEN 1000
#define EOF1 '~'

int mystrend(char s[], char t[]);

main()
{
   char s[MAXLEN];
   char g[MAXLEN];
   int value;

   mygetline(s, MAXLEN);
   mygetline(g, MAXLEN);

   value = mystrend(s, g);
   printf("%d\n", value);
}

int mystrend(char s[], char t[])
{
   int j = 0;

   while(*s)
   {
      //printf("%c %c\n", *s, *(t + j));
      if(*s++ == *(t + j))
         j++;
      else
         j = 0;
   }

   if(!*(t + j))
      return 1;
   else
      return 0;
}

