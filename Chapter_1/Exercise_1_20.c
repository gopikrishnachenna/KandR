/*
 * Exercise 1-20. Write a program detab that replaces tabs in the input with the
 * proper number of blanks to space to the next tab stop. Assume a fixed set of
 * tab stops, say every n columns. Should n be a variable or a symbolic parame-
 * ter?
 */

#include <stdio.h>

#define MAXLINE 1000
#define EOF1 '~'
#define TABCOL 8

int mygetline(char a[], int lim);
void detab(char mod[], char line[]);

main()
{
   char line[MAXLINE];
   char modline[MAXLINE];
   int len = 0;

   while((len = mygetline(line, MAXLINE)) > 0)
   {
      detab(modline, line);
      printf("%s", modline);
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

void detab(char modline[], char line[])
{
   int i = 0, j = 0;
   int spaces = 0;

   for(i = 0, j = 0; line[i] != '\0'; i++)
   {
      if(line[i] == '\t')
      {
         spaces = (TABCOL - (j % TABCOL));
         while(spaces > 0)
         {
            modline[j++] = ' ';
            spaces--;
         }
      }
      else
         modline[j++] = line[i];

   }
   modline[j] = '\0';
}
