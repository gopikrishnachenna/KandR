/*
 * Exercise 6-2. Write a program that reads a C program and prints in alphabeti-
 * cal order each group of variable names that are identical in the first 6 charac-
 * ters, but different somewhere thereafter.  Don't count words within strings and
 * comments. Make 6 a parameter that can be set from the command line.
 */

/*
 * Even though the program asks for C program checking. Testing with actual C programs
 * is troublesome. getword function is the main change if C program is considered.
 * This program will take normal text as input.
 */

#include "allheader.h"

#define WORD_DEFAULT_LEN 6

struct subtree
{
   char *word;
   struct subtree *left;
   struct subtree *right;
};

struct tnode
{
   char *word;
   int count;
   struct tnode *left;
   struct tnode *right;
   struct subtree *root;
};

static int num = WORD_DEFAULT_LEN;

struct tnode * addtree(struct tnode *p, char *word);
struct subtree * addsubtree(struct subtree *p, char *word);
void printtree(struct tnode *p);
void printsubtree(struct subtree *p);
void freetree(struct tnode *p);
void freesubtree(struct subtree *p);
struct tnode * treealloc(void);
struct subtree * subtreealloc(void);
char *mystrdup(char *s);
void countsubtree(struct subtree *p, int *count);

void main(int argc, char *argv[])
{
   char word[MAXWORDLEN];
   struct tnode *root = NULL;

   if(argc > 1)
      num = atoi(argv[1]);
      
   while(getword(word, MAXWORDLEN) != EOF1)
   {
      root = addtree(root, word);   
   }

   if(NULL != root)
   {
      printtree(root);
      freetree(root);
   }
   printf("##########################################################################\n");
}

struct tnode * addtree(struct tnode *p, char *word)
{
   int cond;

   if(NULL == p)
   {
      if((p = treealloc()) == NULL)
      {
         printf("Error in allocation of memory for tree.\n");
         return p;
      }
      if((p->word = (char *)malloc(num + 1)) == NULL)
      {
         printf("Error in string allocation of memory.\n");
         return p;
      }
      strncpy(p->word, word, num);
      p->left = p->right = NULL;
      p->root = NULL;
      p->count = 1;
      p->root = addsubtree(p->root, word);
   }
   else if((cond = strncmp(word, p->word, num)) == 0)
   {
      p->count++;
      p->root = addsubtree(p->root, word);
   }
   else if(cond < 0)
      p->left = addtree(p->left, word);
   else
      p->right = addtree(p->right, word);

   return p;
}

struct subtree *addsubtree(struct subtree *p, char *word)
{
   int cond;

   if(NULL == p)
   {
      if((p = subtreealloc()) == NULL)
      {
         printf("Error in allocation of memory for subtree.\n");
         return p;
      }
      if((p->word = mystrdup(word)) == NULL)
      {
         printf("Error in string allocation of memory in subtree.\n");
         return p;
      }
      p->left = NULL;
      p->right = NULL;
   }
   else if((cond = strcmp(word, p->word)) > 0)
      p->right = addsubtree(p->right, word);
   else if(cond < 0)
      p->left = addsubtree(p->left, word);

   return p;
}

void printtree(struct tnode *p)
{
   int count = 0;

   if(NULL != p)
   {
      printtree(p->left);
      count = 0;
      countsubtree(p->root, &count);
      if(count > 1)
      {
         printf("##########################################################################\n");
         printsubtree(p->root);
      }
      printtree(p->right);
   }
}

void printsubtree(struct subtree *p)
{
   if(NULL != p)
   {
      printsubtree(p->left);
      printf("%s\n",p->word);
      printsubtree(p->right);
   }
}

void freetree(struct tnode *p)
{
   if(NULL != p)
   {
      freetree(p->left);
      freetree(p->right);
      freesubtree(p->root);
      free(p->word);
      free(p);
   }
}

void freesubtree(struct subtree *p)
{
   if(NULL != p)
   {
      freesubtree(p->left);
      freesubtree(p->right);
      free(p->word);
      free(p);
   }
}

struct tnode * treealloc(void)
{
   return (struct tnode *)malloc(sizeof(struct tnode));
}

struct subtree * subtreealloc(void)
{
   return (struct subtree *)malloc(sizeof(struct subtree));
}

char *mystrdup(char *s)
{
   char *t;

   t = (char *)malloc(strlen(s) + 1);
   strcpy(t, s);
   return t;
}

void countsubtree(struct subtree *p, int *count)
{
   if(NULL != p)
   {
      (*count)++;
      countsubtree(p->left, count);
      countsubtree(p->right, count);
   }
}


