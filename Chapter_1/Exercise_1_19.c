/*
 * Exercise 1-19. Write a function reverse(s) that reverses the character
 * string s. Use it to write a program that reverses its input a line at a time.
 */

#include <stdio.h>

#define EOF1 '~'
#define MAXLINE 1000

int mygetline(char a[], int lim);
void reverse(char a[]);

main()
{
   char line[MAXLINE];
   int len = 0;

   while((len = mygetline(line, MAXLINE)) > 0)
   {
      reverse(line);
      printf("%s",line);
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

void reverse(char line[])
{
   int i = 0, j = 0;
   int len = 0;
   char copyline[MAXLINE];

   while((copyline[i] = line[i]) != '\0')
      i++;

   len = i;

   for(i = (len - 1); i >= 0; i--)
   {
      line[len - 1 - i] = copyline[i];  
   }
   line[len] = '\0';
}
