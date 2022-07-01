/*
 * Exercise 5-16. Add the -d ("directory order") option, which makes comparis-
 * ons only on letters, numbers and blanks. Make sure it works in conjunction with -f
 */

#include <stdio.h>
#include "allheader.h"
#include <string.h>

#define MAXLINES 5000
#define DCHECK(s) (isspace(s) || isalpha(s) || isdigit(s))

void swap(char *s[], int i, int j);
void qsort(char *lineptr[], int left, int right, int (*comp)(const char *, const char *, int, int), int r, int f, int d);
int mystrcmp(const char *s, const char *t, int f, int d);
int numcmp(const char *, const char *, int f, int d);

void main(int argc, char *argv[])
{
   int nlines;
   char *lineptr[MAXLINES];
   int r = 0, f = 0, d = 0;
   int p, count = 0;
   int (*compare)(const char *, const char *, int f, int d);
   
   compare = mystrcmp;

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
            switch(p)
            {
               case 'n':
                  compare = numcmp;
                  break;
               case 'r':
                  r = 1;
                  break;
               case 'f':
                  f = 1;
                  break;
               default:
                  printf("Invalid options.\n");
                  return;
                  break;
               case 'd':
                  d = 1;
                  break;
            }
         }
      }
      else
      {
         printf("Options should start with -\n");
         return;
      }
   }

   //printf("%s %s\n", (c ? "NUMCMP" : "STRCMP"), (n ? "REVERSE" : "STRAIGHT"));

   if((nlines = myreadlines(lineptr, MAXLINES)) >= 0)
   {
      qsort(lineptr, 0, nlines - 1, compare, r, f, d);
      mywritelines(lineptr, nlines);
   }
   else
      printf("Too many lines to sort.\n");
}

void qsort(char *lineptr[], int left, int right, int (*comp)(const char *, const char *, int, int), int rev, int fold, int dir)
{
   int last, i;

   if(left >= right)
      return;
   swap(lineptr, left, (left + right) / 2);
   last = left;
   for(i = left + 1; i <= right; i++)
   {
      if(rev == 0)
      {
         if((*comp)(lineptr[i], lineptr[left], fold, dir) < 0)
            swap(lineptr, ++last, i);
      }
      else
      {
         if((*comp)(lineptr[i], lineptr[left], fold, dir) > 0)
            swap(lineptr, ++last, i); 
      }
   }
   swap(lineptr, left, last);
   qsort(lineptr, left, last - 1, comp, rev, fold, dir);
   qsort(lineptr, last + 1, right, comp, rev, fold, dir);
}

void swap(char *s[], int i, int j)
{
   char *temp;
   temp = s[i];
   s[i] = s[j];
   s[j] = temp;
}

int numcmp(const char *s, const char *t, int fold, int dir)
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

int mystrcmp(const char *s, const char *t, int fold, int dir)
{
   int i, j;
   char sm[MAXLEN];
   char tm[MAXLEN];

   strcpy(sm, s);
   strcpy(tm, t);

   if(dir == 1)
   {
      for(i = 0, j = 0; s[i] != '\0'; i++)
      {
         if(DCHECK(s[i]))
            sm[j++] = s[i];
      }
      sm[j] = '\0';
      for(i = 0, j = 0; t[i] != '\0'; i++)
      {
         if(DCHECK(t[i]))
            tm[j++] = t[i];
      }
      tm[j] = '\0';
   }

   if(fold == 1)
   {
      for(i = 0, j = 0; sm[i] != '\0'; i++)
      {
            sm[j++] = tolower(sm[i]);
      }
      sm[j] = '\0';
      for(i = 0, j = 0; tm[i] != '\0'; i++)
      {
            tm[j++] = tolower(tm[i]);
      }
      tm[j] = '\0';
   }

   //printf("%s - %s", sm, tm);

   for(i = 0; sm[i] == tm[i] && sm != '\0'; i++) 
      ;

   //printf("%d\n", sm[i] - tm[i]);

   return (sm[i] - tm[i]);
}
