/*
 * Exercise 7-4. Write a private version of scanf analogous to
 * minprintf from the previous section.
 */

#include "allheader.h"

int minscanf(char *fmt, ...);

main()
{
   char line[MAXLEN];
   char name[MAXLEN];
   int age;
   int day, month, year;

   printf("Please enter the data in the following format :\n");
   printf("Name : <name>\n");
   printf("Age : <age>\n");
   printf("DOB : <dd-mm-yyyy>\n");

   printf("#######################################################################################################\n");

   minscanf("Name : %s\n", name);
   minscanf("Age : %d\n", &age);
   minscanf("DOB : %d-%d-%d", &day, &month, &year);

   printf("#######################################################################################################\n");

   printf("Name : %s\n", name);
   printf("Age : %d\n", age);
   printf("DOB : %d-%d-%d\n", day, month, year);
   printf("#######################################################################################################\n");

}

/* This scanf will take white spaces into consideration.*/
int minscanf(char *fmt, ...)
{
   int count = 0;
   va_list ap;
   char *p, *sval;
   int *ival;
   double *fval;
   int i, c;

   va_start(ap, fmt);

   for(p = fmt; *p; p++)
   {
      if(*p != '%')
      {
         //printf("%c\n", *p);
         if(*p != getch())
            return count;
         continue;
      }

      switch(*++p)
      {
         case 'd':
            ival = va_arg(ap, int *);
            scanf("%d", ival);
            count++;
            break;
         case 'f':
            fval = va_arg(ap, double *);
            scanf("%f", fval);
            count++;
            break;
         case 's':
            sval = va_arg(ap, char *);
            for(i = 0; !isspace(c = getch()); i++)
            {
               *(sval + i) = c;
            }
            ungetch(c);
            *(sval + i) = '\0';
            //printf("%s",sval);
            count++;
            break;
         default:
            printf("Unknown identifier.\n");
            break;
      }
   }

   return count;
}

