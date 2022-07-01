/*
 * Exercise 8-4. The standard library function
 *
 * int fseek(FILE  *fp, long offset,  int origin)
 * 
 * is identical to lseek except that fp is a file pointer instead of a file descriptor
 * and the return value is an int status, not a position. Write fseek.
 * Make sure that your fseek coordinates properly with the buffering done for the other
 * functions of the library.
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
int myfseek(MYFILE *fp, long offset,  int origin);

void main(void)
{
   MYFILE *fp, *fpo;
   int c, i;

   fp = myfopen("file2.txt", "r");
   fpo = myfopen("file3.txt", "w");

   if(fp == NULL)
   {
      printf("Error !\n");
      return;
   }

   myfseek(fp, 5, 0);
   for(i = 0; i < 5; i++)
      myputc(mygetc(fp), fpo);
   myputc('\n',fpo);
   myfseek(fp, 40, 0);
   for(i = 0; i < 5; i++)
      myputc(mygetc(fp), fpo);
   myputc('\n',fpo);
   myfseek(fp, 130, 1);
   for(i = 0; i < 5; i++)
      myputc(mygetc(fp), fpo);
   myputc('\n',fpo);
   myfseek(fp, -180, 1);
   for(i = 0; i < 5; i++)
      myputc(mygetc(fp), fpo);
   myputc('\n',fpo);
   myfseek(fp, -5, 2);
   for(i = 0; i < 5; i++)
      myputc(mygetc(fp), fpo);
   myputc('\n',fpo);
   myfseek(fp, -40, 2);
   for(i = 0; i < 5; i++)
      myputc(mygetc(fp), fpo);


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

int myfseek(MYFILE *fp, long offset,  int origin)
{
   int b;
   int n;

   if(NULL == fp)
      return -1;

   b = (fp->flags.unbuf == 1) ? 1 : BUFSIZE;

   //printf("%d %d %d %d %d\n", origin, fp->flags.read, offset, b, fp->count);

   if(1 == origin)
   {
      if(offset <= fp->count && offset >= (fp->base - fp->ptr))
      {
         fp->count -= offset;
         fp->ptr += offset;
         fp->flags.eof = 0;
         return 0;
      }
      else
         offset -= fp->count;
   }
   
   if(-1 == (n = lseek(fp->fd, offset, origin)))
      return -1;

   //printf("%d\n", n);

   if(fp->base == NULL)
      if((fp->base = (char *)malloc(b)) == NULL)
         return -1;

   fp->ptr = fp->base;

   if(fp->flags.read == 1)
      fp->count = 0;
   else
      fp->count = b;

   fp->flags.eof = 0;

   return 0;
}

