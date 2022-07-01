/*
 * Exercise 7-5. Rewrite the postfix calculator of Chapter 4 to use scanf
 * and/or sscanf to do the input and number conversion
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

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
#define MAXLEN 1000

void push(double p);
double pop(void);
int getch(void);
void ungetch(int c);
int getop(char s[]);
void clear(void);
char getcommand(char s[]);

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
            //printf("%f ", atof(s));
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
            printf("Unknown command passed - %s %c\n", s, type);
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
   printf("%.8g\n", pop());
   return 0;
}

int getop(char si[])
{
   char s[MAXLEN];
   int c;

   scanf("%s", s);

   if(strlen(s) == 1 && !isalpha(s[0]) && !isdigit(s[0]))
      return s[0];

   strcpy(si, s);

   if(isdigit(s[0]) || s[0] == '.' || s[0] == '-' || s[0] == '+')
   {
      return NUMBER;
   }

   return getcommand(s);
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


