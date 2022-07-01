/*
 * Exercise 8-1.  Rewrite  the program cat from Chapter 7 using read, write, open 
 * and close instead of their standard  library equivalents.  Perform experi-
 * ments to determine the relative speeds of the two versions
 */

#include "allheader.h"

#define BUFSIZE 100

void main(int argc, char *argv[])
{
   int fd;
   int n;
   char buf[BUFSIZE];

   while(--argc)
   {
      fd = open(*++argv, O_RDONLY, 0);
      printf("################### %s ###################\n", *argv);
      if(fd == -1)
         fprintf(stderr, "Unable to open the file %s.", *argv);

      while((n = read(fd, buf, BUFSIZE)) > 0)
      {
         if(write(1, buf, n) != n)
            fprintf(stderr, "Failed to write to file %s.", *argv);
      }

      close(fd);
      printf("######################################################\n");
   }

   return;
}
