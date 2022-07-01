/*
 * Exercise 4-13. Write a recursive version of the function reverse  (s),  which
 * reverses the string s in place.
 */

#include <stdio.h>
#include <string.h>

#define MAXLEN 1000

int mygetline(char s[], int lim);
void reverse(char s[]);
void swap(char s[], int i, int j);

main()
{
   int n;
   char s[MAXLEN];

   while(mygetline(s, MAXLEN) > 0)
   {
      for(n = 0; s[n] != '\n'; n++)
         ;
      s[n] = '\0';
      reverse(s);
      printf("%s\n",s);
   }
}

void reverse(char s[])
{
   static int i = 0;

   if(i < strlen(s)/2)
   {
      swap(s, i, strlen(s) - 1 - i);
      i++;
      reverse(s);
   }
   else
      i = 0;
}

void swap(char s[], int i, int j)
{
   char temp;

   temp = s[j];
   s[j] = s[i];
   s[i] = temp;
}
