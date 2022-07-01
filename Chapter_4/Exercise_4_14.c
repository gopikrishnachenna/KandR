/*
 * Exercise 4-14. Define a macro swap(t,x,y) that interchanges two arguments
 * of type t. (Block structure will help).
 */

#include <stdio.h>
#include <string.h>

#define MAXLEN 1000

#define SWAP(T, A, B) \
{\
   T temp;\
   temp = A;\
   A = B;\
   B = temp;\
}

int mygetline(char s[], int lim);
void reverse(char s[]);

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
      SWAP(char, s[i], s[strlen(s) - 1 - i]);
      i++;
      reverse(s);
   }
   else
      i = 0;
}
