/*
 * Exercise 5-13. Write the program tail, which prints the last n lines of its
 * input. By default, n is 10, let us say, but it can be changed by an optional
 * argument, so that
 *    tail -n
 * prints the last n lines. The program should behave rationally no matter how
 * unreasonable the input or the value of n.  Write the program so it makes the
 * best use of available storage; lines should be stored as in the sorting program of
 * Section 5.6, not in a two-dimensionalarray of fixed size.
 */

#include <stdio.h>
#include "allheader.h"

#define MAXLEN 1000
#define EOF1 '~'
#define MAXLINES 1000

static int n = 10;

void main(int argc, char *argv[])
{
   int nlines;
   char *lineptr[MAXLINES];

   if(argc > 2)
   {
      printf("Too many arguments.\n");
      return;
   }

   if(2 == argc)
   {
      if('-' != **++argv)
      {
         printf("Options should start with -.\n");
         return;
      }
      n = atoi(*argv + 1);
      printf("Number of lines = %d\n", n);
      if(n < 0)
      {
         printf("Negative line number is not accepted.\n");
         return;
      }
   }

   if((nlines = myreadlines(lineptr, MAXLINES)) > 0)
   {
      n = (nlines > n) ? n : nlines;
      while(n)
      {
         printf("%s\n", lineptr[nlines - n]);
         n--;
      }
   }

   return;
}
