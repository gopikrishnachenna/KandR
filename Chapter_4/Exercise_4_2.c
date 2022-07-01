/*
 * Exercise 4-2. Extend atof to handle scientific notation of the form
 * 123.45e-6
 * where a floating-point number may be followed by e or E and an optionally
 * signed exponent.
 */

#include <stdio.h>

#define MAXLEN 1000
#define EOF1 '~'

int mygetline(char line[], int lim);
double myatof(char s[]);

main()
{
   char line[MAXLEN];
   double value;

   while(mygetline(line, MAXLEN) > 0)
   {
      value = myatof(line);
      printf("%lf\n", value);
   }
}

int mygetline(char line[], int lim)
{
   int i = 0;
   char c;

   while(--lim > 0 && (c = getchar()) != EOF1 && c != '\n')
      line[i++] = c;

   if(c == '\n')
      line[i++] = c;

   line[i] = '\0';

   return i;
}

double myatof(char s[])
{
   double val, power;
   int i = 0, sign;
   int exp, esign;

   while(isspace(s[i]))
   {
      i++;
      continue;
   }

   sign = (s[i] == '-') ? -1 : 1;
   if(s[i] == '-' || s[i] == '+')
      i++;

   for(val = 0; isdigit(s[i]); i++)
      val = 10 * val + s[i] - '0';
   if(s[i] == '.')
      i++;
   for(power = 1; isdigit(s[i]); i++)
   {
      val = 10 * val + s[i] - '0';
      power = power * 10;
   }
 
   if(s[i] == 'e' || s[i] == 'E')
      i++;
   esign = (s[i] == '-') ? -1 : 1;
   if(s[i] == '-' || s[i] == '+')
      i++;
   for(exp = 0; isdigit(s[i]); i++)
      exp = 10 * exp + s[i] - '0';

   for(i = 0; i < exp; i++)
      power = (esign == 1) ? power / 10 : power * 10;

   return sign * val / power;
}

