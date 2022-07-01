/*
 * Exercise 2-5. Write the function any(s1,s2), which returns the first location
 * in the string s1 where any character from the string s2 occurs, or -1
 * if s1 contains no characters from s2. (The standard library function strpbrk
 * does the same job but returns a pointer to the location.
 *
 * Works for only words. Will improve it once getline comes in.
 */

#include <stdio.h>

#define MAXLEN 1000

int any(char s1[], char s2[]);

main()
{
   char input[MAXLEN];
   char detect[MAXLEN];
   int value;
   
   printf("Enter the input string - ");
   scanf("%s", input);
   printf("Enter the string char to be detected - ");
   scanf("%s", detect);

   value = any(input, detect);

   if(-1 == value)
      printf("No match found.\n");
   else
      printf("Position in string - %d\n", value + 1);
}

int any(char s1[], char s2[])
{
   int i, j;
   int position = 0;

   for(i = 0; s1[i] != '\0'; i++)
   {
      for(j = 0; s2[j] != '\0'; j++)
         if(s1[i] == s2[j])
            return i;
   }
   return -1;
}

