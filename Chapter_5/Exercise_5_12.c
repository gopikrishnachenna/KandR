/*
 * Exercise 5-12. Extend entab and detab to accept the shorthand
 *    entab -m +n
 * to mean tab stops every n columns, starting at column m.
 * Choose convenient (for the user) default behavior.
 */

#include <stdio.h>

#define MAXLINE 1000
#define EOF1 '~'
#define TABCOL n
#define ENTAB 1
#define DETAB 0
#define INVALID -1

static int n = 8;
static int m = 0;

int mygetline(char a[], int lim);
void detab(char mod[], char line[]);
void entab(char modline[], char line[]);

void main(int argc, char *argv[])
{
   char line[MAXLINE];
   char modline[MAXLINE];
   int len = 0;
   int flag = INVALID;

   if(argc < 2 || argc > 4)
   {
      printf("Invalid arguments. \n");
      return;
   }

   while(--argc)
   {
      switch(**++argv)
      {
         case '-':
            m = atoi(*argv + 1);
            printf("m = %d\n",m);
            break;
         case '+':
            n = atoi(*argv + 1);
            printf("n = %d\n",n);
            break;
         case 'e':
            flag = ENTAB;
            printf("Entab.\n");
            break;
         case 'd':
            flag = DETAB;
            printf("Detab.\n");
            break;
         default:
            printf("Invalid options.\n");
            return;
      }
   }

   if(INVALID == flag)
   {
      printf("Entab or detab option is mandatory.\n");
      return;
   }

   while((len = mygetline(line, MAXLINE)) > 0)
   {
      if(DETAB == flag)
      {
         detab(modline, line);
         printf("%s", modline);
      }
      else if(ENTAB == flag)
      {
         entab(modline, line);
         printf("%s", modline);
      }
   }
   return;
}

int mygetline(char s[], int lim)
{
   int c;
   int i, len;

   for(i = 0, len = 0; ((c = getchar()) != EOF1) && c != '\n'; i++)
   {
      if(i < (lim - 1))
         s[len++] = c;
   }

   if(len == i && i < (lim - 1) && c == '\n')
   {
      s[len++] = c;
      i++;
   }
   s[len] = '\0';

   return i;
}

void detab(char modline[], char line[])
{
   int i = 0, j = 0, k = 0;
   int spaces = 0;

   for(i = 0; line[i] != '\0'; i++)
   {
      if(line[i] == '\t')
      {
         spaces = (TABCOL - (k % TABCOL));
         if(k < m)
         {
            modline[j++] = '\t';
            k += spaces;
         }
         else
         {
            while(spaces > 0)
            {
               modline[j++] = ' ';
               k++;
               spaces--;
            }
         }
      }
      else
      {
         modline[j++] = line[i];
         k++;
      }
   }
   modline[j] = '\0';
}

void entab(char modline[], char line[])
{
   int i = 0, j = 0, k = 0;
   int spaces = 0;

   for(i = 0; line[i] != '\0'; i++)
   {
      if(line[i] != ' ')
      {
         while(spaces > 0)
         {
            modline[j++] = ' ';
            spaces--;
         }
         modline[j++] = line[i];
      }
      else
      {
         spaces++;
         if(1 == (TABCOL - (i % TABCOL)))
         {
            if(i >= m)
            {
               modline[j++] = '\t';
               spaces = 0;
            }
            else
            {
               while(spaces > 0)
               {
                  modline[j++] = ' ';
               }
            }
         }
      }
   }
   modline[j] = '\0';
}

