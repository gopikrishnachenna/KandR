/*
 * Exercise 8-6. The standard  library  function calloc (n, size) returns a 
 * pointer to n  objects of size size, with the storage initialized to zero. 
 * Write calloc, by calling mal1oc or by modifying it.
 */

#include "allheader.h"

void *mycalloc(size_t nitems, size_t size);

main()
{
/* Not going to write code. Too easy. */
}

void *mycalloc(size_t nitems, size_t size)
{
   char *p;
   int i;

   p = (char *)malloc(size * nitems);

   if(p == NULL)
      return p;

   for(i = 0; i < (size * nitems); i++)
      *(p + i) = 0;

   return (void *)p;
}

