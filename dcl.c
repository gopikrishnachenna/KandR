#include <stdio.h>
#include <string.h>
#include "allheader.h"

void dcl(void)
{
   int nc = 0;

   while(gettoken() == '*')
      nc++;

   //printf("before directdlc()\n");

   directdcl();
   //printf("after directdlc()\n");

   while(nc--)
      strcat(out, " pointer to");

   return;
}

void directdcl(void)
{
   int type = -1;     

   //printf("Entered directdcl\n");

   if('(' == tokentype)
   {
      dcl();
      if(')' != tokentype)
      {
         printf("Error - No closing bracket.\n");
         return;
      }
   }
   else if(tokentype == NAME)
      strcpy(name, token);
   else if(tokentype != '\n' && tokentype != EOF1)
   {
      strcpy(name, ""); /* Recover from missing name */
      printf("Error - expected name or ()\n", tokentype);
      type = tokentype;
   }
   else
      return;

   if(-1 == type)
      type = gettoken();

   //printf("firsthalf dcl done\n");

   while(type == BRACKETS || type == PARENS)
   {
      if(type == PARENS)
         strcat(out, " function returning");
      else
      {
         strcat(out, " array");
         strcat(out, token);
         strcat(out, " of");
      }
      type = gettoken();
   }

   //printf("Exit dcl\n");
}

int gettoken(void)
{
   int c;
   char *p = token;

   while((c = getch()) == ' ' || c == '\t')
      ;

   while(!isalnum(c) && strchr("*\n()[~_", c) == NULL)
      c = getch();

   if(c == '(')
   {
      if((c = getch()) == ')')
      {
         strcpy(token, "()");
         return tokentype = PARENS;
      }
      else
      {
         ungetch(c);
         return tokentype = '(';
      }
   }
   else if(c == '[')
   {
      for(*p++ = c; (c = getch()) != ']';)
      {
         if(!isdigit(c) && c != ' ' && c != '\t')
         {
            ungetch(c);
            break;
         }
         *p++ = c;
      }
      *p++ = ']';
      *p = '\0';
      return tokentype = BRACKETS;
   }
   else if(isalpha(c))
   {
      for(*p++ = c; isalnum(c = getch());)
         *p++ = c;
      ungetch(c);
      *p = '\0';
      return tokentype = NAME;
   }
   else
      return tokentype = c;
}

void undcl(void)
{
   char words[MAXSPLITS][MAXWORD];
   int p, countl = 0;
   char temp[MAXLEN];

   p = splitline(inputs, words);

   if(p <= 0)
      return;

   strcat(out, words[countl++]);

   //printf("out = %s, p = %d\n", out, p);

   while(--p > 1)
   {
      if(strstr("*", words[countl]))
      {
         if(countl == p || words[countl + 1][0] == '*')
            sprintf(temp, "*%s", out);
         else
            sprintf(temp, "(*%s)", out);
         strcpy(out, temp);
      }
      else if(strstr("()", words[countl]))
         strcat(out, words[countl]);
      else if(words[countl][0] == '[')
         strcat(out, words[countl]);
      countl++;
   }

   sprintf(temp, "%s %s", words[countl], out);
   strcpy(out, temp);
}

