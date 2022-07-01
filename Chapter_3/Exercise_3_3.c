/*
 * Exercise 3-3. Write a function expand(s1,s2) that expands shorthand nota-
 * tions like a-z in the string s1 into the equivalent complete list abc...xyz
 * in s2. Allow for letters of either case and digits, and be prepared to handle cases
 * like a-b-c and a-zO-9 and -a-z. Arrange that a leading or trailing - is taken literally.
 */

#include <stdio.h>
#include <string.h>

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

int check(char a, char b)
{

   //printf("%c %c\n", a, b);
   if(a > b)
      return 1;

   if(a >= 'a' && a <= 'z' && b >= 'a' && b <= 'z')
      return 0;

   if(a >= 'A' && a <= 'Z' && b >= 'A' && b <= 'Z')
      return 0;

   if(a >= '0' && a <= '9' && b >= '0' && b <= '9')
      return 0;

   return 1;
}

void expand(char t[], char s[])
{
   int i, j = 0;
   char first, last, k;

   for(i = 0; s[i] != '\0'; i++)
   {
      if(s[i] != '-')
      {
         t[j++] = s[i];
      }
      else
      {
         //printf("Entered %d\n", i);
         if(i == 0 || i == strlen(s))
         {
            t[j++] = s[i];
            continue;
         }
         first = s[i - 1];
         last = s[i + 1];

         if(check(first, last))
         {
            t[j++] = s[i];
            continue;
         }

         //printf("check failed.\n");

         for(k = first + 1; k < last; k++)
            t[j++] = k;
      }
   }
   t[j] = '\0';
}

void main(void)
{
   int len = 0;
   char line[MAXLEN];
   char result[MAXLEN];

   while((len = mygetline(line, MAXLEN)) > 0)
   {
      expand(result, line);
      printf("%s", line);
      printf("%s", result);
   }
}

