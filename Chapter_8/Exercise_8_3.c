/*
 * Exercise 8-3. Design and write _flushbuf, fflush, and fclose.
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

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

#define PERMS 0666

#define feof(p) (((p)->flags & _EOF) != 0)
#define ferror(p) (((p)->flags & _ERROR) != 0)
#define fileno(p) ((p)->fd)
#define mygetc(p) (((--(p)->count) >= 0) ? (unsigned char)*(p)->ptr++ : _myfillbuf(p))
#define getchar() getc(stdin)
#define myputc(x, p) (((--(p)->count) >= 0) ? *(p)->ptr++ = (x) : _myflushbuf((x), (p)))
#define putchar(c) myputc((c), stdout)

MYFILE *myfopen(char *name, char *mode);
int _myfillbuf(MYFILE *fp);
int myfflush(MYFILE *fp);

void main(void)
{
   MYFILE *fp, *fpo;
   int c;

   fp = myfopen("file2.txt", "r");
   fpo = myfopen("file3.txt", "w");

   if(fp == NULL)
   {
      printf("Error !\n");
      return;
   }

   while((c = mygetc(fp)) != EOF)
      myputc(c, fpo);

   //myfflush(fpo);
   myfclose(fp);
   myfclose(fpo);
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

int _myflushbuf(int c, MYFILE *fp)
{
   int b;
   int n;

   if(fp->flags.write != 1 || fp->flags.eof != 0 || fp->flags.error != 0)
      return EOF;

   b = (fp->flags.unbuf == 1) ? 1 : BUFSIZE;

   if(fp->base == NULL)
   {
      if((fp->base = (char *)malloc(b)) == NULL)
         return EOF;
   }
   else
   {
      n = write(fp->fd, fp->base, fp->ptr - fp->base);
      if(n != (fp->ptr - fp->base))
      {
         fp->flags.error = 1;
         return EOF;
      }
   }

   fp->ptr = fp->base;
   *fp->ptr++ = c;
   fp->count = b - 1;

   return c;
}

int myfflush(MYFILE *fp)
{
   if(NULL == fp)
      return EOF;

   return _myflushbuf(EOF, fp);
}

int myfclose(MYFILE *fp)
{
   if(NULL == fp)
      return EOF;

   if(fp->flags.write == 1 && myfflush(fp) == EOF)
      return EOF;

   if(close(fp) == EOF)
      return EOF;

   free(fp->base);
   fp->flags.read = fp->flags.write = fp->flags.unbuf = fp->flags.error = fp->flags.eof = 0;

   return 0;
}
