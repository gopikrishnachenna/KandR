/*
 * Exercise 3-2. Write a function escape(s, t) that converts characters like
 * newline and tab into visible escape sequences like \n and \t as it copies the
 * string t to s. Use a switch. Write a function for the other direction as well,
 * converting escape sequences into the real characters.
 */

#include <stdio.h>

#define EOF1 '~'
#define MAXLEN 1000

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

void escape(char t[], char s[])
{
   int i, j = 0;

   for(i = 0; s[i] != '\0'; i++)
   {
      switch(s[i])
      {
         case '\n':
            t[j++] = '\\';
            t[j++] = 'n';
            break;
         case '\t':
            t[j++] = '\\';
            t[j++] = 't';
            break;
         default :
            t[j++] = s[i];
            break;
      }
   }

      t[j] = '\0';
}

void revescape(char t[], char s[])
{
   int i, j = 0;

   for(i = 0; s[i] != '\0'; i++)
   {
      if(s[i] == '\\')
      {
         switch(s[i + 1])
         {
            case 'n':
               t[j++] = '\n';
               i++;
               break;
            case 't':
               t[j++] = '\t';
               i++;
               break;
            default :
               t[j++] = s[i++];
               t[j++] = s[i];
               break;
         }
      }
      else
         t[j++] = s[i];
   }

   t[j] = '\0';
}

void main(void)
{
   int len = 0;
   char line[MAXLEN];
   char result[MAXLEN];
   char revresult[MAXLEN];

   while((len = mygetline(line, MAXLEN)) > 0)
   {
      escape(result, line);
      revescape(revresult, result);
      printf("%s", line);
      printf("%s\n", result);
      printf("%s", revresult);
   }
}

