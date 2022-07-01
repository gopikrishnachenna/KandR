/*
 * Exercise 6-1. Our version of getword does not properly handle underscores,
 * string constants, comments, or preprocessor control lines. Write a better ver-
 * sion
 */

#include <stdio.h>
#include "allheader.h"

#define MAXLEN 1000
#define UNDERSCORE '_'

int getword(char *word, int lim);

main()
{
   char word_string[MAXLEN];

   while(getword(word_string, MAXLEN) != EOF1)
      if(strlen(word_string) > 1)
         printf("%s\n", word_string);
}

int getword(char *word, int lim)
{
   char c;
   char *w = word;

   while(isspace(c = getch()))
      ;

   if(c != EOF1)
      *w++ = c;

   if(!isalpha(c) && c != UNDERSCORE)
   {
      /* String constants */
      if(c == '"')
         while((c = getch()) != EOF1)
            if(c == '"')
               break;

      /* Comments */
      if(c == '/')
      {
         if((c = getch()) == '*')
         {
            while((c = getch()) != EOF1)
            {
               if(c == '*')
               {
                  if((c = getch()) == '/')
                     break;
                  else
                     ungetch(c);
               }
            }
         }
         else
         {
            ungetch(c);
            c = '/';
         }
      }

      /* Preprocessor */
      if(c == '#')
      {
         char d = c;
         do
         {
            while((c = getch()) != '\n')
               d = c;
         } while(d == '\\');
         c = '#';  
      }
              
      *w = '\0';
      return c;
   }

   for(; --lim > 0; w++)
      if(!isalnum(*w = getch()) && *w != UNDERSCORE)
      {
         ungetch(*w);
         break;
      }

   *w = '\0';

   return word[0];
}

