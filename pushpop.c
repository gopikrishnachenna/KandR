/*
 * Functions for push and pop of stack.
 */

#include <stdio.h>

#define STACKLENGTH 1000

double stack[STACKLENGTH];
int sp = 0;

void push(double p)
{
   if(sp >= STACKLENGTH)
      printf("Stack overflow.\n");
   else
      stack[sp++] = p;
}

double pop(void)
{
   if(sp <= 0)
      printf("Stack is empty.\n");
   else
      return stack[--sp];

   return 0.0;
}

void clear(void)
{
   sp = 0;
}
