/*
 * Exercise 4-3. Given the basic framework, it's straightforward to extend the cal-
 * culator. Add the modulus (%) operator and provisions for negative numbers.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100
#define NUMBER '0'
#define EOF1 '~'

void push(double p);
double pop(void);
int getch(void);
void ungetch(int c);
int getop(char s[]);

main()
{
   int type;
   double op2;
   char s[MAXOP];

   while((type = getop(s)) != EOF1)
   {
      switch(type)
      {
         case NUMBER:
            push(atof(s));
            break;
         case '+':
            push(pop() + pop());
            break;
         case '-':
            op2 = pop();
            push(pop() - op2);
            break;
         case '*':
            push(pop() * pop());
            break;
         case '/':
            op2 = pop();
            if(0 != op2)
               push(pop() / op2);
            else
               printf("Division by zero is not allowed.");
            break;
         case '%':
            op2 = pop();
            if(op2 > 0 )
               push((int)pop() % (int)op2);
            else
               printf("Modulus by zero and negative numbers is not allowed.");
            break;
         case '\n':
            printf("%.8g\n", pop());
            break;
         default:
            printf("Unknown command passed - %s", s);
            break;
      }
   }
   return 0;
}

int getop(char s[])
{
   int i = 0, c;

   while((s[0] = c = getch()) == ' ' || c == '\t')
      ;
   s[1] = '\0';

   if(!isdigit(c) && c != '.' && c != '+' && c != '-')
      return c;

   if(c == '+' || c == '-')
   {
      char sign = c;
      if(isdigit(c = getch()))
      {
         s[i++] = sign;
         s[i] = c;
      }
      else
      {
         ungetch(c);
         return sign;
      }
   }

   if(isdigit(c))
      while(isdigit(s[++i] = c = getch()))
         ;
   if(c == '.')
      while(isdigit(s[++i] = c = getch()))
         ;

   s[i] = '\0';
   if(c != EOF1)
      ungetch(c);

   return NUMBER;
}
