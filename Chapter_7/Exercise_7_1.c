/*
 * Exercise 7-1. Write a program that converts upper case to lower or lower case
 * to upper, depending on the name it is invoked with, as found in argv[0].
 */

#include "allheader.h"

#define LOWER 0
#define UPPER 1

void main(int argc, char *argv[])
{
   int flag = LOWER;
   int c;
   
   if(strstr(argv[0], "upper") != NULL)
   {
      //printf("yosha\n");
      flag = UPPER;
   }

   while((c = getchar()) != EOF1)
      if(flag == UPPER)
         putchar(toupper(c));
      else if(flag == LOWER)
         putchar(tolower(c));

}
