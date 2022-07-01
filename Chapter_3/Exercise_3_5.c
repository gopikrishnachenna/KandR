/*
 * Exercise 3-5. Write the function itob(n, s, b) that converts the integer
 * n into a  base b character  representation  in the  string s.  
 * In particular, itob(n, s, 16) formats n as a hexadecimal integer in s.
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

void myitob(int n, char a[], int b)
{
   int sign = n;
   int i = 0;
   int flag = 0;
   int result;

   if(n - 1 > n)
   {
      n = -(n + 1);
      flag = 1;
   }
   else if(sign < 0)
      n = -n;

   do
   {
      result = n % b;
      a[i++] = (result > 9) ? (result - 10) + 'a' : result + '0';
   }
   while((n /= b) != 0);

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
   printf("Enter the base - ");
   scanf("%d", &b);

   myitob(c, a, b);

   printf("%s\n", a);
}

