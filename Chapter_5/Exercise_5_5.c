/*
 * Exercise 5-5. Write versions of the library functions strncpy, strncat, and strncmp;
 * which operate on at most the first n characters of their argument strings. For example,
 * strncpy(s, t ,n) copies at most n characters of t to s. Full descriptions are in Appendix B
 */

#include <stdio.h>
#include "allheader.h"
#include <string.h>

#define MAXLEN 1000
#define EOF1 '~'

#define MIN(A, B) (((A) < (B)) ? (A) : (B))  

void mystrncat(char s[], char t[], int n);
void mystrncpy(char s[], char t[], int n);
int mystrncmp(char s[], char t[], int n);

main()
{
   char s[MAXLEN];
   char g[MAXLEN];
   char r[MAXLEN];

   mygetline(s, MAXLEN);
   mygetline(g, MAXLEN);

   strcpy(r, s);
   mystrncat(r, g, 5);
   printf("Concatenated string :\t\t\t\t %s\n", r);
   strcpy(r, s);
   mystrncpy(r, g, 5);
   printf("Copied string :\t\t\t\t\t %s\n", r);
   printf("%d\n", mystrncmp(s, g, 5));
}

void mystrncat(char s[], char t[], int n)
{
   int count = 0;
   
   while(*s++)
      ;

   s--;

   while(count++ < n && (*s++ = *t++))
      ;

   if(count == n + 1)
      *s = '\0';
}

void mystrncpy(char s[], char t[], int n)
{
   int count = 0;

   while(count++ < n && (*s++ = *t++))
      ;

   if(count == n + 1)
      *s = '\0';
}

int mystrncmp(char s[], char t[], int n)
{
   int count = 0;
   int flag = (strlen(s) == strlen(t));

   for(;count < n && (*s == *t); count++, s++, t++)
   {
      if(*s == '\0')
         return (flag ? 0 : -1);
      if(*t == '\0')
         return (flag ? 0 : 1);
   }

   if(n == count)
      return 0;
   else
      return (*s > *t) ? 1 : -1;
}

