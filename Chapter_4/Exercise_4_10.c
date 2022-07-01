/*
 * Exercise 4-10. An alternate organization uses getline to read an entire input
 * line; this makes getch and  ungetch unnecessary. Revise the calculator to use
 * this approach.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'
#define EOF1 '~'
#define SINE '@'
#define EXPONENT '#'
#define POWER '$'
#define PRINTTOP '!'
#define DUPLICATE '('
#define SWAP '^'
#define CLEAR '&'

void push(double p);
double pop(void);
int getop(char s[], char line[]);
void clear(void);
char getcommand(char s[]);

int line_i;

main()
{
   int type;
   double op2, op3;
   char s[MAXOP];
   char line[1000];

   while(mygetline(line, 1000) > 0)
   {
      line_i = 0;
      while((type = getop(s, line)) != '\0')
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
            case PRINTTOP:
               op2 = pop();
               push(op2);
               printf("The top element of stack is %.8g\n",op2);
               break;
            case DUPLICATE:
               op2 = pop();
               push(op2);
               push(op2);
               break;
            case SWAP:
               op2 = pop();
               op3 = pop();
               push(op2);
               push(op3);
               break;
            case CLEAR:
               clear();
               break;
            case SINE:
               push(sin(pop()));
               break;
            case EXPONENT:
               push(exp(pop()));
               break;
            case POWER:
               op2 = pop();
               op3 = pop();
               if(op3 == 0 && op2 <= 0)
                  printf("Negative power for 0 is not allowed.\n");
               else
               {
                  if(op3 < 0)
                     op2 = (int)op2;
                  push(pow(op3, op2)); /* Restrictions to be added here. */
               }
               break;
         }
      }
   }
   return 0;
}

int getop(char s[], char line[])
{
   int i = 0, c;

   while((s[0] = c = line[line_i++]) == ' ' || c == '\t')
      ;
   s[1] = '\0';

   if(!isdigit(c) && c != '.' && c != '+' && c != '-' && !isalpha(c))
      return c;

   if(c == '+' || c == '-')
   {
      char sign = c;
      if(isdigit(c = line[line_i++]))
      {
         s[i++] = sign;
         s[i] = c;
      }
      else
      {
         line_i--;
         return sign;
      }
   }

   if(isalpha(c))
   {
      while(isalpha(s[++i] = c = line[line_i++]))
         ;
      s[i] = '\0';
      line_i--;
      return getcommand(s);
   }

   if(isdigit(c))
      while(isdigit(s[++i] = c = line[line_i++]))
         ;

   if(c == '.')
      while(isdigit(s[++i] = c = line[line_i++]))
         ;

   s[i] = '\0';
      
   line_i--;

   return NUMBER;
}

char getcommand(char s[])
{
   if(strcmp(s, "print") == 0)
      return PRINTTOP;
   else if(strcmp(s, "duplicate") == 0)
      return DUPLICATE;
   else if(strcmp(s, "swap") == 0)
      return SWAP;
   else if(strcmp(s, "clear") == 0)
      return CLEAR;
   else if(strcmp(s, "sin") == 0)
      return SINE;
   else if(strcmp(s, "exp") == 0)
      return EXPONENT;
   else if(strcmp(s, "power") == 0)
      return POWER;

   return -1;
}


