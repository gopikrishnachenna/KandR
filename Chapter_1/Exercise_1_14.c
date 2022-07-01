/*
 * Exercise 1-14. Write a program to print a histogram of the frequencies of dif-
 * ferent characters in its input.
 */

#include <stdio.h>

#define EOF1 '~'
#define MAX_LENGTH_WORD 26



main()
{
   int arr[MAX_LENGTH_WORD];
   int i, len = 0, maxlen = 0, j, c;

   for(i = 0; i < MAX_LENGTH_WORD; i++)
      arr[i] = 0;

   while((c = getchar()) != EOF1)
   {
      if(c >= 'A' && c <= 'Z')
      {
         arr[c - 'A']++;  
      }
      else if(c >= 'a' && c <= 'z')
      {
         arr[c - 'a']++;
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
      for(j = 0; j < MAX_LENGTH_WORD; j++)
      {
         if(arr[j] >= i)
            printf("*\t");
         else
            printf(" \t");
      }
      printf("\n");
   }

   for(j = 0; j < MAX_LENGTH_WORD; j++)
   {
      printf("\t%c", j+'A');
   }
   printf("\n");
}
