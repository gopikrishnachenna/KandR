/*
 * Exercise 1-22. Write a program to "fold" long input lines into two or more
 * shorter lines after the last non-blank character that occurs before the n-th
 * column of input. Make sure your program does something intelligent with very
 * long lines, and if there are no blanks or tabs before the specified column
 */

#include <stdio.h>
#include "allheader.h"

#define MAXLINE 1000
#define COLUMN 21
#define FULLLEN 80

int mygetline(char a[], int lim);
void append(char line[], char sub[]);
int printfold(char line[]);
int trim(char line[], int trimlen);

main()
{
   char line[MAXLINE];
   char linemax[FULLLEN];
   int len = 0;
   linemax[0] = '\0';
   int count = 0;
   int trimlen = 0;

   while((len = mygetline(line, COLUMN)) > 0)
   {
      append(linemax, line);  
      //printf("line - %s linemax - %s", line, linemax);
      do
      {
         trimlen = printfold(linemax);
         count = trim(linemax, trimlen);
      }
      while(count > COLUMN);
   }
   if(count > 0)
      printfold(linemax);
   return 0;
}

int mygetline(char s[], int lim)
{
   int c, i;

   for(i = 0; i<lim-1 && (c = getchar()) != EOF1 && c != '\n'; i++)
         s[i] = c;

   if(c == '\n')
   {
      s[i] = c;
      i++;
   }

   s[i] = '\0';
   return i;
}

int trim(char line[], int trimlen)
{
   int i, count = trimlen + 1, len = 0;

   while(line[count] == '\n' || line[count] == ' ' || line[count] == '\t')
      count++;

   for(i = count; line[i] != '\0'; i++, len++)
      line[len] = line[i];

   line[len] = '\0';

   //printf("len - %d\n", len);

   return len;
}

void append(char line[], char sub[])
{
   int i = 0, count = 0;

   while(line[count] != '\0')
      count++;

   //printf("count before = %d\n", count);

   while((line[count++] = sub[i++]) != '\0')
      ;

   //printf("count after = %d\n", count);
}


int printfold(char line[])
{
   int i, end, space = 0;
   char modline[COLUMN];

   for(i = 0; i < (COLUMN - 1) && line[i] != '\n' && line[i] != '\0'; i++)
   {
      if(line[i] == ' ' || line[i] == '\t')
         space = i;
   }

   //printf("space = %d, i = %d\n", space, i);

   if((COLUMN - 1) != i)
      end = i - 1;
   else if(0 == space)
      end = COLUMN;
   else
      end = space - 1;

   //printf("end = %d\n", end);

   for(i = 0; i <= end; i++)
   {
      modline[i] = line[i];
      //printf("%c ", modline[i]);
   }

   //printf("%d\n",i);
   modline[i] = '\0';

   //printf("%s\n", line);
   printf("%s\n", modline);
   //printf("%c %c %c %c\n", modline[1], modline[2], modline[3], modline[4]);
   //printf("return value = %d\n", end);

   return end;
}

