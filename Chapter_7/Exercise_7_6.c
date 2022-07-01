/*
 * Exercise 7-6. Write a program to compare two files, printing the first line
 * where they differ.
 */

#include "allheader.h"

void main(int argc, char *argv[])
{
   FILE *fp1, *fp2;
   char line1[MAXLEN], line2[MAXLEN];
   char *s1, *s2;
   int found = 0;

   if(argc != 3)
   {
      printf("Usage : ./a.out <file1> <file2>\n");
      exit(1);
   }

   fp1 = fopen(argv[1], "r");
   fp2 = fopen(argv[2], "r");

   while((s1 = fgets(line1, MAXLEN, fp1)) != NULL)
   {
      if((s2 = fgets(line2, MAXLEN, fp2)) == NULL)
      {
         break;
      }

      if(strcmp(line1, line2) != 0)
      {
         found = 1;
         break;
      }
   }

   if(s2 && found == 0)
      s2 = fgets(line2, MAXLEN, fp2);

   if(s1 != NULL)
      printf("%s : %s", argv[1], line1);
   if(s2 != NULL)
      printf("%s : %s", argv[2], line2);

   exit(0);
}
