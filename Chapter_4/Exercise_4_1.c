/*
 * Exercise 4-1. Write the function strrindex(s, t), which returns the position of the
 * rightmost occurrence of t in s, or -1 if there is none.
 */

#include <stdio.h>

#define MAXLEN 1000
#define EOF1 '~'

int mygetline(char line[], int lim);
int mystrrindex(char string[], char searchfor[]);

char search[] = "ould";

main()
{
   int found = 0;
   char line[MAXLEN];
   int pos;

   while(mygetline(line, MAXLEN) > 0)
      if((pos = mystrrindex(line, search)) != -1)
      {
         printf("Position = %d\n", pos);
         printf("%s", line);
         found++;
      }

   return found;
}

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

int mystrrindex(char s[], char pat[])
{
   int i, j, k;
   int value = -1;

   for(i = 0; s[i] != '\0'; i++)
   {
      for(j = i, k = 0; pat[k] != '\0' && s[j] == pat[k]; j++, k++)
         ;
      if(k > 0 && pat[k] == '\0')
         value = i;
   }
   
   return value;
}

