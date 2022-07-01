/*
 * Exercise 7-3. Revise minprintf to handle more of the other facilities of
 * printf.
 */

#include "allheader.h"

int minprintf(char *fmt, ...);

main()
{
   int count;

   count = minprintf("Integer is %d", 20);  
   minprintf(" %d\n", count);
   count = minprintf("Float is %-10f", 56.2342);
   minprintf(" %d\n", count);
   count = minprintf("Float is %-10.2f", 56.2342);
   minprintf(" %d\n", count);
   count = minprintf("Float is %-10.6f", 56.2342);
   minprintf(" %d\n", count);
   count = minprintf("Float is %10.6f", 56.2342);
   minprintf(" %d\n", count);
   count = minprintf("Float is %3.1f", 56.2342);
   minprintf(" %d\n", count);
   count = minprintf("Integer is %10d", 56);
   minprintf(" %d\n", count);
   count = minprintf("Integer is %-10d", 56);
   minprintf(" %d\n", count);
   count = minprintf("String is %s.", "Yosha");
   minprintf(" %d\n", count);
   count = minprintf("String is %s.", "hello, world");
   minprintf(" %d\n", count);
   count = minprintf("String is %10s.", "hello, world");
   minprintf(" %d\n", count);
   count = minprintf("String is %.10s.", "hello, world");
   minprintf(" %d\n", count);
   count = minprintf("String is %-10s.", "hello, world");
   minprintf(" %d\n", count);
   count = minprintf("String is %.15s.", "hello, world");
   minprintf(" %d\n", count);
   count = minprintf("String is %-15s.", "hello, world");
   minprintf(" %d\n", count);
   count = minprintf("String is %15.10s.", "hello, world");
   minprintf(" %d\n", count);
   count = minprintf("String is %-15.10s.", "hello, world");
   minprintf(" %d\n", count);
}

int minprintf(char *fmt, ...)
{
   char *p, *sval;
   va_list ap;
   int ival;
   double fval;
   int count = 0;
   char prefix[10];
   int prefix_int = 0;


   va_start(ap, fmt);
   for(p = fmt; *p; p++)
   {
      if(*p != '%')
      {
         putchar(*p);
         count++;
         continue;
      }

      prefix[0] = '\0';
      prefix_int = 0;
      p++;

      if(*p == '-')
      {
         strcat(prefix, "-");
         p++;
      }

      //printf("\n after - %s\n", prefix);

      while(isdigit(*p))
      {
         prefix_int = 10 * prefix_int + (*p - '0');
         p++;
      }

      if(prefix_int)
      {
         sprintf(prefix, "%s%d", prefix, prefix_int);
         prefix_int = 0;
      }

      //printf("\n after digit %s\n", prefix); 

      if(*p == '.')
      {
         strcat(prefix, ".");
         p++;
      }

      while(isdigit(*p))
      {
         prefix_int = 10 * prefix_int + (*p - '0');
         p++;
      }

      if(prefix_int)
         sprintf(prefix, "%s%d", prefix, prefix_int);

      if(*p == 'h' || *p == 'l')
      {
         strcat(prefix, (*p == 'h') ? "h" : "l");
         p++;
      }
      //printf("\n after every %s\n", prefix); 
      
      switch(*p)
      {
         case 'd':
            ival = va_arg(ap, int);
            if(strlen(prefix))
            {
               char temp[MAXLEN];
               sprintf(temp, "%%%sd", prefix);
               strcpy(prefix, temp);
               count += printf(prefix, ival);
            }
            else
               count += printf("%d", ival);
            break;
         case 'f':
            fval = va_arg(ap, double);
            if(strlen(prefix))
            {
               char temp[MAXLEN];
               sprintf(temp, "%%%sf", prefix);
               strcpy(prefix, temp);
               count += printf(prefix, fval);
            }
            else
               count += printf("%f", fval);
            break;
         case 's':
               if(strlen(prefix))
               {
                  char temp[MAXLEN];
                  char temp1[MAXLEN];
                  temp[0] = '\0';
                  //printf("\n prefix = %s\n", prefix);
                  for(sval = va_arg(ap, char *); *sval; sval++)
                     sprintf(temp, "%s%c", temp, *sval);
                  sprintf(temp1, "%%%ss", prefix);
                  strcpy(prefix, temp1);
                  //printf("\n prefix = %s, temp = %s\n", prefix, temp);
                  count += printf(prefix, temp);
               }
               else
                  for(sval = va_arg(ap, char *); *sval; sval++)
                     count += printf("%c", *sval);
               break;
         default:
            putchar(*p);
            count++;
            break;
      }
   }

   va_end(ap);

   return count;
}
