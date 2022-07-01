/*
 * Exercise 4-12. Adapt the ideas of printd   to write a recursive versionof i toa;
 * that is, convert an integer into a string by calling a recursive routine.
 */

#include <stdio.h>

int myitoa(int n, char s[]);

main()
{
   int n;
   char s[1000];

   printf("Enter the integer - ");
   scanf("%d", &n);

   s[0] = '\0';

   if(-1 != myitoa(n, s))
      printf("%s\n",s);
}

int myitoa(int n, char s[])
{
   int sign = 0;
   int i;

   if(n < 0)
   {
      s[0] = '-';
      s[1] = '\0';
      n = -n;
   }

   if(n / 10)
      myitoa(n / 10, s);

   for(i = 0; s[i] != '\0'; i++)
      ;
   s[i++] = n % 10 + '0';
   s[i] = '\0';
}
