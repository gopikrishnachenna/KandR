/*
 * Exercise 1-23. Write a program to remove all comments from a C program.
 * Don't forget to handle quoted strings and character constants properly. C com-
 * ments do not nest.
 */

#include <stdio.h>

#define MAXLINE 1000
#define EOF1 '~'
#define OUTSIDE 1
#define INSIDE 0

int mygetline(char a[], int lim);

main()
{
   char line[MAXLINE + 1];
   int len = 0;
   int i, state = OUTSIDE;

   while((len = mygetline(line, MAXLINE)) > 0)
   {
            
      for(i = 0; line[i] != '\0'; i++)
      {
         if(OUTSIDE == state)
         {
            if(line[i] == '/' && line[i + 1] == '*')
            {
               //printf("Entered");
               state = INSIDE;
               i++;
            }
            if(line[i] == '/' && line[i + 1] == '/')
            {
               printf("\n");
               break;
            }
         }
         else
         {
            //printf("omit");
            if(line[i] == '*' && line[i + 1] == '/')
            {
               //printf("Exit");
               state = OUTSIDE;
               i++;
               continue;
            }
         }
         if(OUTSIDE == state)
            printf("%c", line[i]);
      }
   }

   return 0;
}

int mygetline(char s[], int lim)
{
   int c, i;

   for(i = 0; i<lim-1 && (c = getchar()) != EOF1 && c != '\n'; i++)
         s[i] = c;

   if(c == '\n')
   {
      s[i] = c;
      i++;
   }

   s[i] = '\0';
   return i;
}
