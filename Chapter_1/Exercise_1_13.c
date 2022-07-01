/*
 * Exercise 1-13. Write a program to print a histogram of the lengths of words in
 * its input. It is easy to draw the histogram with the bars horizontal; a vertical
 * orientation is more challenging.
 */

#include <stdio.h>

#define EOF1 '~'
#define MAX_LENGTH_WORD 25



main()
{
   int arr[MAX_LENGTH_WORD];
   int i, len = 0, maxlen = 0, j, c;

   for(i = 0; i < MAX_LENGTH_WORD; i++)
      arr[i] = 0;

   while((c = getchar()) != EOF1)
   {
      if(c == ' ' || c == '\t' || c == '\n')
      {
         if(len != 0)
            arr[len]++;
         len = 0;
      }
      else
      {
         len++;
      }
   }
   if(len != 0)
      arr[len]++;
   len = 0;

   for(i = 0; i < MAX_LENGTH_WORD; i++)
   {
      if(arr[i] > maxlen)
         maxlen = arr[i];
      printf("%d ", arr[i]);
   }
   

   printf("%d\n",maxlen);

   for(i = maxlen; i > 0; i--)
   {
      printf("\t");
      for(j = 1; j < MAX_LENGTH_WORD; j++)
      {
         if(arr[j] >= i)
            printf("*\t");
         else
            printf(" \t");
      }
      printf("\n");
   }

}
