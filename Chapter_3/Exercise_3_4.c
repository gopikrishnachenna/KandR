/*
 * Exercise 3-4. In a two's complement number representation, our version of
 * itoa does not handle the largest negative number, that is, the value of
 * n equal to -(2^(wordsize-1)). Explain why not.  
 * Modify it to print that value correctly, regardless of the machine on which it runs.
 */

#include <stdio.h>
#include <string.h>

#define MAXLEN 1000

void reverse(char line[])
{
   int i = 0, j = 0;
   int len = 0;
   char copyline[MAXLEN];

   while((copyline[i] = line[i]) != '\0')
      i++;

   len = i;

   for(i = (len - 1); i >= 0; i--)
   {
      line[len - 1 - i] = copyline[i];  
   }
   line[len] = '\0';
}

void myitoa(int n, char a[])
{
   int sign = n;
   int i = 0;
   int flag = 0;

   if(n - 1 > n)
   {
      n = -(n + 1);
      flag = 1;
   }
   else if(sign < 0)
      n = -n;

   do
   {
      a[i++] = n % 10 + '0';
   }
   while((n /= 10) != 0);

   if(sign < 0)
      a[i++] = '-';
   a[i] = '\0';
   
   if(flag == 1)
   {
      for(i = 0; a[i] == 9; i++)
         a[i] = 0;
      a[i]++;
   }

   reverse(a);
}

void main(void)
{
   int c;
   char a[MAXLEN];
   
   printf("Enter an integer - ");
   scanf("%d", &c);

   myitoa(c, a);

   printf("%s\n", a);
}

