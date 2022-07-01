/*
 * Exercise 5-3. Write a pointer version of the function strcat that we showed in Chapter 2:
 * strcat(s ,t) copies the string t to the end of s
 */

#include <stdio.h>
#include "allheader.h"

#define MAXLEN 1000
#define EOF1 '~'

void mystrcat(char s[], char t[]);

main()
{
   char s[MAXLEN];
   char g[MAXLEN];

   mygetline(s, MAXLEN);
   mygetline(g, MAXLEN);

   mystrcat(s, g);
   printf("Concatenated string : %s", s);
}

void mystrcat(char s[], char t[])
{
   
   while(*s++)
      ;

   s--;

   while(*s++ = *t++)
      ;
}

