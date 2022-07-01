/*
 * Exercise 5-18. Make dcl recover from input errors. 
 */

#include <stdio.h>
#include <string.h>
#include "allheader.h"

void main(void)
{
   while(gettoken() != EOF1)
   {
      if(tokentype == '\n')
         continue;
      datatype[0] = '\0';
      //printf("Entered\n");
      strcpy(datatype, token);
      //printf("copied datatype\n");
      out[0] = '\0';
      name[0] = '\0';
      //printf("before dcl\n");
      dcl();
      //printf("after dcl\n");
      printf("%s :%s %s\n", name, out, datatype);
      if(tokentype != '\n')
      {
         printf("syntax error %c .\n", tokentype);
         break;
      }
   }
}
