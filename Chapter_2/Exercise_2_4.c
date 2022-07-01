/*
 * Exercise 2-4. Write an alternate version of squeeze (s1,s2)
 * that deletes each character in s1 that matches any character in the
 * string s2.
 *
 * Works for only words. Will improve it once getline comes in.
 */

#include <stdio.h>

#define MAXLEN 1000

void squeeze(char s1[], char s2[]);

main()
{
   char input[MAXLEN];
   char remove[MAXLEN];
   
   printf("Enter the input string - ");
   getline(input, MAXLEN);
   printf("Enter the string char to be removed - ");
   getline(remove, MAXLEN);

   squeeze(input, remove);

   printf("Final string - %s\n", input);
}

void squeeze(char s1[], char s2[])
{
   int i, j, k = 0;
   int flag = 0;

   for(i = 0; s1[i] != '\0'; i++)
   {
      flag = 0;
      for(j = 0; s2[j] != '\0'; j++)
         if(s1[i] == s2[j])
         {
            flag = 1;
            break;
         }
      if(!flag)
         s1[k++] = s1[i];
   }
   s1[k] = '\0';
}

