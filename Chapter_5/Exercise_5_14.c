/*
 * Exercise 5-14. Modify the sort program to handle a -r flag, which indicates
 * sorting in reverse (decreasing) order. Be sure that -r works with -n.
 */

#include <stdio.h>
#include "allheader.h"
#include <string.h>

#define MAXLINES 5000
#define STRCMP 0
#define NUMCMP 1
#define STRAIGHT 0
#define REVERSE 1

void swap(char *s[], int i, int j);
void qsort(char *lineptr[], int left, int right, int (*comp)(const char *, const char *), int v);
int numcmp(const char *, const char *);

void main(int argc, char *argv[])
{
   int nlines;
   char *lineptr[MAXLINES];
   int c = STRCMP;
   int n = STRAIGHT;
   int p, count = 0;

   if(argc > 3)
   {
      printf("Too many arguments.\n");
      return;
   }

   //printf("arguments = %d\n", argc);

   while(--argc)
   {
      count = 0;
      if(**++argv == '-')
      {
         while(p = *(*argv + ++count))
         {
            //printf("%c\n", p);
            if('n' == p)
               c = NUMCMP;
            else if('r' == p)
               n = REVERSE;
            else
            {
               printf("Invalid options.\n");
               return;
            }
         }
      }
      else
      {
         printf("Options should start with -\n");
         return;
      }
   }

   printf("%s %s\n", (c ? "NUMCMP" : "STRCMP"), (n ? "REVERSE" : "STRAIGHT"));

   if((nlines = myreadlines(lineptr, MAXLINES)) >= 0)
   {
      if(NUMCMP == c)
         qsort(lineptr, 0, nlines - 1, numcmp, n);
      else
         qsort(lineptr, 0, nlines - 1, strcmp, n);
      mywritelines(lineptr, nlines);
   }
   else
      printf("Too many lines to sort.\n");
}

void qsort(char *lineptr[], int left, int right, int (*comp)(const char *, const char *), int rev)
{
   int last, i;

   if(left >= right)
      return;
   swap(lineptr, left, (left + right) / 2);
   last = left;
   for(i = left + 1; i <= right; i++)
   {
      if(rev == STRAIGHT)
      {
         if((*comp)(lineptr[i], lineptr[left]) < 0)
            swap(lineptr, ++last, i);
      }
      else
      {
         if((*comp)(lineptr[i], lineptr[left]) > 0)
            swap(lineptr, ++last, i); 
      }
   }
   swap(lineptr, left, last);
   qsort(lineptr, left, last - 1, comp, rev);
   qsort(lineptr, last + 1, right, comp, rev);
}

void swap(char *s[], int i, int j)
{
   char *temp;
   temp = s[i];
   s[i] = s[j];
   s[j] = temp;
}

int numcmp(const char *s, const char *t)
{
   double v1, v2;

   v1 = atoi(s);   /* For some reason atof is not working */
   v2 = atoi(t);   /* For some reason atof is not working */
   //printf("%f %f\n", v1, v2);
   if(v1 < v2)
      return -1;
   else if(v2 < v1)
      return 1;
   else
      return 0;
}
