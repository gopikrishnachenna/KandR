/*
 * Exercise 5-7. Rewrite readlines to store lines in an array supplied by main, rather 
 * than calling alloc to maintain storage.  How much faster is the program?
 */

#include <stdio.h>
#include "allheader.h"
#include <string.h>

#define MAXLINES 5000


void swap(char s[][MAXLEN], int i, int j);
void qsort(char lineptr[][MAXLEN], int left, int right);

main()
{
   int nlines;
   char lineptr[MAXLINES][MAXLEN];

   if((nlines = myreadlines1(lineptr, MAXLINES)) >= 0)
   {
      qsort(lineptr, 0, nlines - 1);
      mywritelines1(lineptr, nlines);
   }
   else
      printf("Too many lines to sort.\n");
}

void qsort(char lineptr[][MAXLEN], int left, int right)
{
   int last, i;

   if(left >= right)
      return;
   swap(lineptr, left, (left + right) / 2);
   last = left;
   for(i = left + 1; i <= right; i++)
   {
      if(strcmp(lineptr[i], lineptr[left]) < 0)
         swap(lineptr, ++last, i);
   }
   swap(lineptr, left, last);
   qsort(lineptr, left, last - 1);
   qsort(lineptr, last + 1, right);
}

void swap(char s[][MAXLEN], int i, int j)
{
   char temp[MAXLEN];
   strcpy(temp, s[i]);
   strcpy(s[i], s[j]);
   strcpy(s[j], temp);
}

