/*
 * getline functionality. 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "allheader.h"

#define MAXLEN 1000
#define EOF1 '~'

int mygetline(char line[], int lim)
{
   int i = 0;
   char c;

   while(--lim > 0 && (c = getchar()) != EOF1 && c != '\n')
      line[i++] = c;

   if(c == '\n')
      line[i++] = c;

   line[i] = '\0';

   return i;
}

int myreadlines(char *lineptr[], int nlines)
{
   int len;
   char line[MAXLEN];
   int count = 0;
   char *p;

   while((len = mygetline(line, MAXLEN)) > 0)
      if(nlines-- && (p = malloc(len)) != NULL)
      {
         line[len - 1] = '\0';   //Delete the newline.
         strcpy(p, line);
         lineptr[count++] = p;
      }
      else
         return -1;

   return count;
}

void mywritelines1(char lineptr[][MAXLEN], int nlines)
{
   while(nlines--)
      printf("%s\n", *lineptr++);
}

void mywritelines(char *lineptr[], int nlines)
{
   while(nlines--)
      printf("%s\n", *lineptr++);
}

int myreadlines1(char lineptr[][MAXLEN], int nlines)
{
   int len;
   char line[MAXLEN];
   int count = 0;

   while((len = mygetline(line, MAXLEN)) > 0)
      if(nlines--)
      {
         line[len - 1] = '\0';   //Delete the newline.
         strcpy(lineptr[count++], line);
      }
      else
         return -1;

   return count;
}

int splitline(char s[], char t[][MAXWORD])
{
   int nwords = 0, wl = 0;
   int i;

   for(i = 0; i < MAXSPLITS; i++)
      t[i][0] = '\0';

   while(*s)
   {
      if(*s == ' ' || *s == '\t' || *s == '\n')
      {
         t[nwords][wl] = '\0';
         //printf("%s\n", t[nwords]);
         wl = 0;
         if(t[nwords][0] != '\0')
            nwords++;
         if(nwords > MAXSPLITS)
            break;
         s++;
         continue;
      }

      t[nwords][wl++] = *s++;
      
      if(wl > MAXWORD)
         nwords++;
      if(nwords > MAXSPLITS)
         break;
   }

return (t[nwords][0] ? nwords + 1 : nwords);
}

int getword(char *s, int lim)
{
   int c;
   char *w = s;

   *w = '\0';

   while(isspace(c = getch()))
      ;

   if(c == EOF1)
      return c;
   else
      *w++ = c;

   while(--lim && !isspace(c = getch()) && c != EOF1)
      *w++ = c;

   *w = '\0';

   ungetch(c);
   return s[0];
}

int getspaceword(char *s, int lim)
{
   int c;
   char *w = s;

   *w = '\0';

   while(isspace(c = getch()))
      return c;

   if(c == EOF1)
      return c;
   else if(!isalnum(c))
   {
      *w++ = c;
      *w = '\0';
      return c;
   }
   else
      *w++ = c;

   while(--lim && !isspace(c = getch()) && isalnum(c) && c != EOF1)
      *w++ = c;

   *w = '\0';

   ungetch(c);
   return s[0];
}



