/*
 * Exercise 7-9. Functions like isupper can be implemented to save space or to
 * save time. Explore both possibilitie
 */

#include "allheader.h"

static unsigned int isupperarray[256] = {0};

main()
{

/* I dont even want to write code for this */

}

void initisupperarray(void)
{
   int i;

   for(i = 0; i < 256; i++)
      if(i >= 65 && i <= 90)
         isupperarray[i] = 1;
}

int timeisupper(char c)
{
   if(c >= 65 && c <= 90)
      return 1;

   return 0;
}

int spaceisupper(char c)
{
   return isupperarray[c];
}
