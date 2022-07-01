/*
 * Exercise 6-5. Write a function undef that will remove a name and definition
 * from the table maintained by lookup and install.  
 */

#include "allheader.h"

#define HASHINDEX 101

struct nlist
{
   char *name;
   char *defn;
   struct nlist *next;
};

unsigned int hash(char *s);
struct nlist *install(char *name, char *defn);
struct nlist *lookup(char *s);
void undef(char *name);

static struct nlist *hashtab[HASHINDEX];

main()
{

}

unsigned int hash(char *s)
{
   unsigned int result;

   for(result = 0; *s != '\0'; s++)
      result = *s + result * 31;
   
   result = result % HASHINDEX;
   return result;
}

struct nlist *install(char *name, char *defn)
{
   struct nlist *temp;

   if((temp = lookup(name)) == NULL)
   {
      if(   (temp = (struct nlist *)malloc(sizeof(struct nlist))) == NULL
         || (temp->name = strdup(name)) == NULL)
      {
         printf("Error in allocation of memory.\n");
         return NULL;
      }
      temp->next = hashtab[hash(name)];
      hashtab[hash(name)] = temp;
   }
   else
   {
      free((void *)temp->defn);
   }

   if((temp->defn = strdup(defn)) == NULL)
   {
      printf("Error in allocation of memory.\n");
      return NULL;
   }

   return temp;
}

struct nlist *lookup(char *s)
{
   struct nlist *ns;

   for(ns = hashtab[hash(s)]; ns != NULL; ns = ns->next)
      if(strcmp(ns->name, s) == 0)
         return ns;

   return NULL;
}

void undef(char *name)
{
   struct nlist *temp;

   if((temp = lookup(name)) == NULL)
      return;

   temp = hashtab[hash(name)];
   if(strcmp(temp->name, name) == 0)
   {
      free(temp->name);
      free(temp->defn);
      hashtab[hash(name)] = temp->next;
      free(temp);
   }

   for(; strcmp(temp->next->name, name) == 0; temp = temp->next)
      ;

   temp->next = temp->next->next;
   free(temp->next->name);
   free(temp->next->defn);
   free(temp->next);
}

