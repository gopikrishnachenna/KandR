/*
 * Exercise 8-7. malloc accepts a size request without checking its plausibility;
 * free believes that the block it is asked to free contains a valid size field.
 * Improve these routines so they take more pains with error checking.
 */

/* I assume the only check to be done for malloc is check that 
 * it is not negative or zero. But the argument is unsigned so i am stumped as to what the issue is.
 */

/* For free also just check that it has a valid header. The address and size should be non - negative.*/

#include "allheader.h"

void *mymalloc(unsigned nbytes);
void myfree(void *p);
void *morecore(unsigned nbytes);


union header
{
   struct
   {
      union header *ptr;      
      unsigned size;
   }s;
   unsigned long x;
};

typedef union header Header;

static Header *freep = NULL;
static Header base;

main()
{

}

void *mymalloc(unsigned nbytes)
{
   Header *p, *prevp;
   unsigned nblock;

   if(nbytes == 0)
      return NULL;

   nblock = (nbytes + sizeof(Header) - 1)/sizeof(Header) + 1;

   if((prevp = freep) == NULL)
   {
      base.s.ptr = freep = prevp = &base;
      base.s.size = 0;
   }

   for(p = prevp->s.ptr; ; prevp = p, p = p->s.ptr)
   {
      if(p->s.size >= nblock)
      {
         if(p->s.size == nblock)
         {
            prevp->s.ptr = p->s.ptr;
         }
         else
         {
            p->s.size -= nblock;
            p += p->s.size;
            p->s.size = nblock;
         }
         freep = prevp;
         return (void *)(p + 1);
      }

      if(freep == p)
         if((p = morecore(nblock)) == NULL)
            return NULL;
   }
}

void myfree(void *ap)
{
   Header *bp, *p;

   if(NULL == ap)
      return;

   bp = (Header *)ap - 1;

   if(bp->s.size == 0)
      return;

   for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
      if(p > p->s.ptr && (bp > p || bp < p->s.ptr))
         break;

   if(bp + bp->s.size == p->s.ptr)
   {
      bp->s.size += p->s.ptr->s.size;
      bp->s.ptr = p->s.ptr->s.ptr;
   }
   else
      bp->s.ptr = p->s.ptr;

   if(p + p->s.size == bp)
   {
      p->s.size += bp->s.size;
      p->s.ptr = bp->s.ptr;
   }
   else
      p->s.ptr = bp;

   freep = p;
}

void *morecore(unsigned nbytes)
{

}

