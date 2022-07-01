/*
 * Exercise 8-2. Rewrite fopen and _fillbuf with fields instead of explicit bit
 * operations. Compare code size and execution speed.
 */

#include "allheader.h"

#define MAXFILE 100
#define BUFSIZE 100

typedef struct
{
   unsigned int read : 1;
   unsigned int write : 1;
   unsigned int unbuf : 1;
   unsigned int eof : 1;
   unsigned int error : 1;
} _flag;

struct _iobuff
{
   int count;
   char *ptr;
   char *base;
   _flag flags;
   int fd;
};

typedef struct _iobuff MYFILE;



#if 1
MYFILE _iob[MAXFILE] = 
{
   {0, (char *)0, (char *)0, {1}, 0},
   {0, (char *)0, (char *)0, {0, 1, 0}, 1},
   {0, (char *)0, (char *)0, {0, 1, 1}, 2}
};
#else
MYFILE _iob[MAXFILE];
#endif

#undef stdin
#undef stdout
#undef stderr
#undef feof
#undef ferror
#undef fileno
#undef getc
#undef getchar

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

#define PERMS 0666

#define feof(p) (((p)->flags & _EOF) != 0)
#define ferror(p) (((p)->flags & _ERROR) != 0)
#define fileno(p) ((p)->fd)
#define mygetc(p) (((--(p)->count) >= 0) ? (unsigned char)*(p)->ptr++ : _myfillbuf(p))
#define getchar() getc(stdin)

MYFILE *myfopen(char *name, char *mode);
int _myfillbuf(MYFILE *fp);

void main(void)
{
   MYFILE *fp;
   int c;

   fp = myfopen("file2.txt", "r");

   if(fp == NULL)
   {
      printf("Error !\n");
      return;
   }

   while((c = mygetc(fp)) != EOF)
      putchar(c);
}

MYFILE *myfopen(char *name, char *mode)
{
   int fd;
   MYFILE *fp;

   if(   strcmp(mode, "r") != 0
      && strcmp(mode, "w") != 0
      && strcmp(mode, "a") != 0)
      return NULL;

   for(fp = _iob; (fp - _iob) < MAXFILE && (fp->flags.read == 1 || fp->flags.write == 1); fp++)
      ;

   if(fp - _iob >= MAXFILE)
      return NULL;

   if(*mode == 'r')
   {
      fd = open(name, O_RDONLY, 0);
   }
   else if(*mode == 'w')
   {
      fd = creat(name, PERMS);
   }
   else
   {
      fd = open(name, O_WRONLY, 0);
      if(fd == -1)
         fd = creat(name, PERMS);
      else
         lseek(fd, 0, 2);
   }
   if(fd == -1)
      return NULL;

   fp->count = 0;
   fp->ptr = NULL;
   fp->base = NULL;
   if(*mode == 'r')
      fp->flags.read = 1;
   else
      fp->flags.write = 1;
   fp->fd = fd;

   return fp;
}

int _myfillbuf(MYFILE *fp)
{
   int b;

   if(fp->flags.read != 1 || fp->flags.eof != 0 || fp->flags.error != 0)
   {
      printf("0x%X.\n", fp->flags);
      return EOF;
   }

   b = (fp->flags.unbuf == 1) ? 1 : BUFSIZE;
   if(fp->base == NULL)
      if((fp->base = (char *) malloc(b)) == NULL)
         return EOF;
   fp->ptr = fp->base;

   fp->count = read(fp->fd, fp->ptr, BUFSIZE);
   if(--fp->count < 0)
   {
      if(fp->count == -1)
         fp->flags.eof = 1;
      else
         fp->flags.error = 1;
      fp->count = 0;
      return EOF;
   }

   return (unsigned char)*fp->ptr++;
}

