/*
 * Exercise 7-8. Write a program to print a set of files, starting each new one on a
 * new page, with a title and a running page count for each file.
 */

#include "allheader.h"

void main(int argc, char *argv[])
{
   FILE *fp;
   int c;
   int page = 1;

   while(--argc > 0)
   {
      fp = fopen(*++argv, "r");
      if(NULL == fp)
         fprintf(stderr, "Error opening the file - %s\n", *argv);

      printf("###############################################");
      printf(" %s ", *argv);
      printf("######################################%4d#####\n",page++);

      while((c = getc(fp)) != EOF)
         putchar(c);
   }

      printf("###########################################################################################################\n");

}
