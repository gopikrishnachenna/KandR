/*
 * Exercise 2·3. Write the function htoi(s), which converts a string of hexa-
 * decimal digits (including an optional Ox or ox) into its equivalent integer value.
 * The allowable digits are 0 through 9, a through f, and A through F
 */

#include <stdio.h>
#include <math.h>

#define MAXLENGTH 1000

long htoi(char s[]);
int ishexalpha(char s);

main()
{
   long value = 0;
   char arr[MAXLENGTH];

   printf("Enter the hex to be coverted - ");
   scanf("%s", arr);

   value = htoi(arr);

   if(-1 != value)
      printf("The integer conversion is - %lu\n", value);
}

int ishexalpha(char s)
{
   if((s >= 'A' && s <= 'F') || (s >= 'a' && s <= 'f'))
      return 1;

   return 0;
}


long htoi(char s[])
{
   int i = 0;
   long n = 0;

   if(s[i] == '0' && (s[i + 1] == 'x' || s[i + 1] == 'X'))
      i = i + 2;

   //printf("i = %d\n",i);

   for( ; s[i] != '\0'; i++)
   {
      if(!isdigit(s[i]) && !ishexalpha(s[i]))
      {
         printf("Not a hexadecimal.\n");
         return -1;
      }
      
      if(isdigit(s[i]))
         n = 16 * n + (s[i] - '0');
   
      if(ishexalpha(s[i]))
         n = 16 * n + (tolower(s[i]) - 'a' + 10);
   }

   return n;
}

