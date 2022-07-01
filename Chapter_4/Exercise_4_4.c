/*
 * Exercise 4-4.  Add commands to print the top element of the stack without pop-
 * ping, to duplicate  it, and to swap the top two elements.  Add a command  to
 * clear the stack.
 */

/*
 * Commands :
 * t - Print the top element of the statck without popping it.
 * d - duplicate the top element.
 * s - swap the top two elements.
 * c - Clear the stack.
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
void clear(void);

main()
{
   int type;
   double op2, op3;
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
            printf("Unknown command passed - %s\n", s);
            break;
         case 't':
            op2 = pop();
            push(op2);
            printf("The top element of stack is %.8g\n",op2);
            break;
         case 'd':
            op2 = pop();
            push(op2);
            push(op2);
            break;
         case 's':
            op2 = pop();
            op3 = pop();
            push(op2);
            push(op3);
            break;
         case 'c':
            clear();
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
