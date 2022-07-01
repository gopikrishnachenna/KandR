/*
 * Exercise 7-7. Modify the pattern finding program of Chapter 5 to take its input
 * from a set of named files or, if no files are named as arguments, from the stand-
 * ard input. Should the file name be printed when a matching line is found?
 */

/* I didnt do it for no files as arguments. Will do it later */

#include "allheader.h"

int main(int argc, char *argv[])
{
   int except = 0, number = 0, found = 0;
   char pattern[MAXLEN], line[MAXLEN];
   FILE *fp;
   int c;
   int lineno;

   while(--argc && **++argv == '-')
   {
      while(c = *++(*argv))
      {
         switch(c)
         {
            case 'x':
               except = 1;
               break;
            case 'n':
               number = 1;
               break;
            default:
               printf("find: illegal option %c\n", c);
               argc = 0;
               found = -1;
               break;
         }
      }
   }

   if(argc == 0)
   {
      printf("Usage : find -x -n pattern.\n");
      return found;
   }

   strcpy(pattern, *argv++);

   while(--argc)
   {
      lineno = 0;
      fp = fopen(*argv, "r");
      while(fgets(line, MAXLEN, fp) != NULL)
      {
         lineno++;
         if((strstr(line, pattern) != NULL) != except)
         {
            printf("%s ", *argv);
            if(number)
               printf("%d:", lineno);
            printf("%s", line);
            found++;
         }
      }
      fclose(fp);
      argv++;
   }

   return found;
}
