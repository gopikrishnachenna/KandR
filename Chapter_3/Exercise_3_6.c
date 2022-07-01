/*
 * Exercise 3-6. Write a version of itoa that accepts three arguments instead of
 * two. The third argument is a minimum field width; the converted number must
 * be padded with blanks on the left if necessary to make it wide enough.
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

void myitoa(int n, char a[], int b)
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
   
   while((i + ((sign > 0) ? 0 : 1)) < b)
      a[i++] = '0';

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
   int b;
   
   printf("Enter an integer - ");
   scanf("%d", &c);
   printf("Enter min width - ");
   scanf("%d", &b);

   myitoa(c, a, b);

   printf("%s\n", a);
}

