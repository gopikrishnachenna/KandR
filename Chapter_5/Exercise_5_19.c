/*
 * Exercise 5-19. Modify undcl  so that it does not add redundant parentheses to
 * declarations.
 */

#include <stdio.h>
#include "allheader.h"

#define MAXLEN 1000

void main(void)
{
   char line[MAXLEN];
   char words[MAXSPLITS][MAXWORD];
   int len;
   int p = 0, i;

   while((len = mygetline(line, MAXLEN)) > 0)
   {
      name[0] = '\0';
      out[0] = '\0';
      token[0] = '\0';
      datatype[0] = '\0';
      inputs[0] = '\0';

      p = splitline(line, words);
      if(p < 4 || words[1][0] != ':')
      {
         printf("Error in the format.\n");
         break;
      }
      
      //printf("%s %s %d\n", words[0], words[p - 1], p);

      strcpy(name, words[0]);
      strcpy(datatype, words[p - 1]);

      for(i = 2; i < (p - 1); i++)
      {
         if(strstr(words[i], "function"))
         {
            strcat(out, " ()");
         }
         else if(strstr(words[i], "pointer"))
         {
            strcat(out, " *");
         }
         else if(strstr(words[i], "array"))
         {
            strcat(out, " ");
            strcat(out, words[i] + 5);
         }
      }

      sprintf(inputs, "%s%s %s\n", name, out, datatype);
      //printf("%s", inputs);
      out[0] = '\0';
      undcl();
      printf("%s\n", out);
   }
}
