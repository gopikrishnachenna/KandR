/*
 * Header for all the additional functions written by me.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAXLEN 1000
#define EOF1 '~'

#define MAXSPLITS 100
#define MAXWORD 20

#define MAXWORDLEN 100

/* dcl file declarations */
#define MAXTOKEN 100

/* Dirent declarations */
#define MAXFILENAME 100

enum
{
   NAME,
   PARENS,
   BRACKETS
};

#ifndef DCL
#define DCL
int tokentype;
char token[MAXTOKEN];
char datatype[MAXTOKEN];
char name[MAXTOKEN];
char out[MAXLEN];
char inputs[MAXLEN];
#endif

/* getch and ungetch declarations */
int getch(void);
void ungetch(int);

/* Stack declarations */
void push(double);
double pop();
void clear(void);

/* getline and writeline and readline declarations */
int mygetline(char s[], int lim);
void mywritelines1(char lineptr[][MAXLEN], int nlines);
void mywritelines(char *lineptr[], int nlines);
int myreadlines1(char lineptr[][MAXLEN], int nlines);
int myreadlines(char *lineptr[], int nlines);

/* dcl file declarations */
void dcl(void);
void directdcl(void);
int gettoken(void);
void undcl(void);

/* split into words */
int splitline(char s[], char t[][MAXWORD]);

/* get each word */
int getword(char *s, int lim);
int getspaceword(char *s, int lim);


