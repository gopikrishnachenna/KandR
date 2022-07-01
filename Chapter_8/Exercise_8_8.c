/*
 * Write a routine bfree(p,n) that will free an arbitrary block p of n characters 
 * into the free list maintained by malloc and free . By using bfree , a user can 
 * add a static or external array to the free list at any time. 
 */

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

void bfree(char *p, unsigned n)
{
   int nblock;
   Header *ap;

   if(n < 2 * sizeof(Header))
      return;

   nblock = n/sizeof(Header);

   ap = (Header *)p;

   ap->s.size = n;
   ap->s.ptr = NULL;

   if(freep == NULL)
   {
      base.s.ptr = freep = &base;
      base.s.size = 0;
   }

   myfree((void *)(ap + 1));
}
