/*
 * Exercise 6-3. Write a cross-referencer that prints a list of all words in a docu-
 * ment, and, for each word, a list of the line numbers on which it occurs. Remove
 * noise words like "the," "and," and so on.
 */

#include "allheader.h"

#define TRUE 1
#define FALSE 0

struct llist
{
   int linenum;
   struct llist *next;
};

struct tree
{
   char *word;
   struct llist *list;
   struct tree *left;
   struct tree *right;
};

struct tree *addtree(struct tree *p, char *w, int *lnum);
void printtree(struct tree *p);
void addlist(struct llist *l, int num);
void freelist(struct llist *l);
void freetree(struct tree *p);
int getwordlnum(char *word, int lim, int *lnum);
void stripword(char *word);
int checkword(char *word);
void printlist(struct llist *l);
int keyword(char *word);
struct tree *mytalloc(void);
char *mystrdup(char *s);
struct llist *mylistalloc(void);
void myswap(char *s, int i, int j);

static int linenum = 1;

char *mainwords[] = 
{
   "I",
   "The",
   "the",
   "as",
   "As"
};

void main(void)
{
   char word[MAXWORDLEN];
   struct tree *root = NULL;

   while(getwordlnum(word, MAXWORDLEN, &linenum) != EOF1)
   {
      //printf("%s - ", word);
      stripword(word);
      if(checkword(word) && keyword(word))
      {
         //printf("%s %d", word, linenum);
         if(strlen(word) > 4)
            root = addtree(root, word, &linenum);
      }
      //printf("\n");
   }

   if(NULL != root)
   {
      //printf("Omg\n");
      printtree(root);
      freetree(root);
   }
}

struct tree *addtree(struct tree *p, char *w, int *lnum)
{
   int cond;

   if(NULL == p)
   {
      if((p = mytalloc()) == NULL)
      {
         printf("Error in allocating memory for tree.");
         return p;
      }
      p->left = p->right = NULL;
      if((p->list = mylistalloc()) == NULL)
      {
         printf("Error in allocation memory for list.");
         return p;
      }
      p->list->linenum = *lnum;
      p->list->next = NULL;
      if((p->word = mystrdup(w)) == NULL)
      {
         printf("Error in allocation memory for word.");
         return p;
      }
      //printf("Added %s\n", p->word);
   }
   else if((cond = strcmp(w, p->word)) == 0)
      addlist(p->list, *lnum);
   else if(cond < 0)
      p->left = addtree(p->left, w, lnum);
   else
      p->right = addtree(p->right, w, lnum);

   return p;
}

void printtree(struct tree *p)
{
   //printf("Entered.\n");
   if(NULL != p)
   {
      //printf("Entered.\n");
      printtree(p->left);
      printf("%s ", p->word);
      printlist(p->list);
      printf("\n");
      printtree(p->right);
   }
}

void addlist(struct llist *l, int num)
{
   while(NULL != l->next)
      l = l->next;
   
   if(l->linenum == num)
      return;

   if((l->next = mylistalloc()) == NULL)
   {
      printf("Error allocating element in list.\n");
      return;
   }
   l = l->next;
   l->linenum = num;
   l->next = NULL;
}

void freelist(struct llist *l)
{
   struct llist *temp = NULL;

   while(NULL != l)
   {
      temp = l->next;
      free(l);
      l = temp;
   }
}

void freetree(struct tree *p)
{
   if(NULL != p)
   {
      freetree(p->left);
      freetree(p->right);
      freelist(p->list);
      free(p);
   }
}

int getwordlnum(char *word, int lim, int *lnum)
{
   int c;
   char *w = word;

   *w = '\0';

   while(isspace(c = getch()))
      if(c == '\n')
         (*lnum)++;
   
   if(c == EOF1)
   {
      return c;
   }

   *w++ = c;

   for(; --lim; w++)
   {
      if(isspace(*w = getch()))
      {
         ungetch(*w);
         break;
      }
   }
   *w = '\0';
   return word[0];
}

void lstripword(char *word)
{
   char *w = word;

   while(!isalpha(*word) && *word != '\0')
      word++;

   while((*w++ = *word++) != '\0')
      ;
}

void reverse(char *word)
{
   int i;

   for(i = 0; i < (strlen(word)/2); i++)
      myswap(word, i, strlen(word) - i - 1);
}

void myswap(char *s, int i, int j)
{
   char temp;
   temp = s[i];
   s[i] = s[j];
   s[j] = temp;
}

void stripword(char *word)
{
   lstripword(word);
   reverse(word);
   lstripword(word);
   reverse(word);
}   

int checkword(char *word)
{
   if(!strlen(word))
      return FALSE;

   while(*word != '\0')
   {
      if(!isalpha(*word))
         return FALSE;
      word++;
   }

   return TRUE;
}
      
void printlist(struct llist *l)
{
   while(l != NULL)
   {
      printf("%d%s", l->linenum, (NULL != l->next) ? ", " : "");
      l = l->next;
   }
}

int keyword(char *word)
{ 
   int i;

   for(i = 0; i < (sizeof(mainwords) / sizeof(mainwords[0])); i++)
      if(strcmp(mainwords[i], word) == 0)
         return FALSE;

   return TRUE;
}

struct tree *mytalloc(void)
{
   return (struct tree *)malloc(sizeof(struct tree));
}

char *mystrdup(char *s)
{
   char *t;

   t = (char *)malloc(strlen(s) + 1);
   strcpy(t, s);
   return t;
}

struct llist *mylistalloc(void)
{
   return (struct llist *)malloc(sizeof(struct llist));
}

