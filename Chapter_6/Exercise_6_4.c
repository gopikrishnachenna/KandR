/*
 * Exercise 6-4. Write a program that prints the distinct words in its input sorted
 * into decreasing order of frequency of occurrence.  Precede each word by its
 * count.
 */

#include "allheader.h"

#define TRUE 1
#define FALSE 0

struct tree
{
   char *word;
   int count;
   struct tree *left;
   struct tree *right;
};

struct wordcount
{
   char *word;
   int count;
};

struct tree *addtree(struct tree *p, char *w);
void copytree(struct tree *p, struct wordcount *w, int *count);
void counttree(struct tree *p, int *count);
void freetree(struct tree *p);
int mygetword(char *word, int lim);
void stripword(char *word);
int checkword(char *word);
struct tree *mytalloc(void);
char *mystrdup(char *s);
struct wordcount *mywordcount(int count);
void myswap(struct wordcount *s, int i, int j);
void printwc(struct wordcount *w, int count);
void mycswap(char *s, int i, int j);
void wcqsort(struct wordcount *w, int lower, int upper);

void main(void)
{
   char word[MAXWORDLEN];
   struct tree *root = NULL;
   struct wordcount *wc = NULL;
   int treecount = 0;

   while(mygetword(word, MAXWORDLEN) != EOF1)
   {
      stripword(word);
      if(checkword(word))
      {
         root = addtree(root, word);
      }
   }

   if(NULL != root)
   {
      counttree(root, &treecount);
      wc = mywordcount(treecount);
      treecount = 0;
      copytree(root, wc, &treecount);
      printwc(wc, treecount);
      wcqsort(wc, 0, treecount - 1);
      printwc(wc, treecount);
      freetree(root);
      free(wc);
   }
}

struct tree *addtree(struct tree *p, char *w)
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
      if((p->word = mystrdup(w)) == NULL)
      {
         printf("Error in allocation memory for word.");
         return p;
      }
      p->count = 1;
   }
   else if((cond = strcmp(w, p->word)) == 0)
      p->count++;
   else if(cond < 0)
      p->left = addtree(p->left, w);
   else
      p->right = addtree(p->right, w);

   return p;
}

void copytree(struct tree *p, struct wordcount *w, int *count)
{
   if(NULL != p)
   {
      copytree(p->left, w, count);
      copytree(p->right, w, count);
      (w + *count)->word = mystrdup(p->word);
      (w + *count)->count = p->count;
      (*count)++;
   }
}

void counttree(struct tree *p, int *count)
{
   if(NULL != p)
   {
      counttree(p->left, count);
      counttree(p->right, count);
      (*count)++;
   }
}

void freetree(struct tree *p)
{
   if(NULL != p)
   {
      freetree(p->left);
      freetree(p->right);
      free(p->word);
      free(p);
   }
}

int mygetword(char *word, int lim)
{
   int c;
   char *w = word;

   *w = '\0';

   while(isspace(c = getch()))
      ;

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
      mycswap(word, i, strlen(word) - i - 1);
}

void mycswap(char *s, int i, int j)
{
   char temp;
   temp = s[i];
   s[i] = s[j];
   s[j] = temp;
}

void myswap(struct wordcount *s, int i, int j)
{
   struct wordcount temp;
   //printf("%s %d %s %d -- ", s[i].word, s[i].count, s[j].word, s[j].count);
   temp = s[i];
   s[i] = s[j];
   s[j] = temp;
   //printf("%s %d %s %d\n", s[i].word, s[i].count, s[j].word, s[j].count);
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

struct wordcount *mywordcount(int size)
{
   return (struct wordcount *)malloc(sizeof(struct wordcount) * size);
}

void printwc(struct wordcount *w, int count)
{
   int i;
   
   printf("##############################################################################################\n");

   for(i = 0; i < count; i++)
      printf("%3d %s\n", w[i].count, w[i].word);
   printf("##############################################################################################\n");
}

void wcqsort(struct wordcount *w, int left, int right)
{
   int mid = (left + right)/2;
   int last = left;
   int i;

   if(left < right)
   {
      myswap(w, left, mid);
      for(i = left + 1; i<= right; i++)
      {
         if(w[i].count < w[left].count)
         {
            myswap(w, ++last, i);
         }
      }
      myswap(w, last, left);
#if 0
      printf("##############################################################################################\n");
      for(i = left; i <= right; i++)
         printf("%s %d %s\n", (i == mid) ? "****" : "", w[i].count, w[i].word);
      printf("##############################################################################################\n");
#endif
      wcqsort(w, left, last - 1);
      wcqsort(w, last + 1, right);
   }
}


