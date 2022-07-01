/*
 * Exercise 8-5. Modify the fsize program to print the other information con-
 * tained in the inode entry.
 */

#include "allheader.h"
#include <pwd.h>
#include <grp.h>
#include <time.h>

void fsize(char *name);
void dirwalk(char *dir, void (*fcn)(char *));

static const char *monthname[] =
{
   "",
   "Jan",
   "Feb",
   "Mar",
   "Apr",
   "May",
   "Jun",
   "Jul",
   "Aug",
   "Sep",
   "Oct",
   "Nov",
   "Dec"
};

typedef struct
{
   ino_t d_ino;
   char d_name[100];
} Dirent;

void main(int argc, char *argv[])
{
   if(argc == 1)
      fsize(".");
   else
      while(--argc)
         fsize(*++argv);

   return;
}

void getperm(mode_t mode, char *s)
{
   if((mode & S_IFMT) == S_IFDIR)
      *s++ = 'd';
   else
      *s++ = '-';

   if((mode & S_IRUSR) == S_IRUSR)
      *s++ = 'r';
   else
      *s++ = '-';

   if((mode & S_IWUSR) == S_IWUSR)
      *s++ = 'w';
   else
      *s++ = '-';

   if((mode & S_IXUSR) == S_IXUSR)
      *s++ = 'x';
   else
      *s++ = '-';

   if((mode & S_IRGRP) == S_IRGRP)
      *s++ = 'r';
   else
      *s++ = '-';

   if((mode & S_IWGRP) == S_IWGRP)
      *s++ = 'w';
   else
      *s++ = '-';

   if((mode & S_IXGRP) == S_IXGRP)
      *s++ = 'x';
   else
      *s++ = '-';

   if((mode & S_IROTH) == S_IROTH)
      *s++ = 'r';
   else
      *s++ = '-';

   if((mode & S_IWOTH) == S_IWOTH)
      *s++ = 'w';
   else
      *s++ = '-';

   if((mode & S_IXOTH) == S_IXOTH)
      *s++ = 'x';
   else
      *s++ = '-';

   *s = '\0';
}

void fsize(char *name)
{
   struct stat stbuf;
   int month, day, hour, min;
   char perm[20];

   if(-1 == stat(name, &stbuf))
   {
      fprintf(stderr, "Unable to get stat of the file %s.\n", name);
      return;
   }

   if((stbuf.st_mode & S_IFMT) == S_IFDIR)
   {
      dirwalk(name, fsize);
   }

   day = localtime(&stbuf.st_mtime)->tm_mday;
   hour = localtime(&stbuf.st_mtime)->tm_hour;
   min = localtime(&stbuf.st_mtime)->tm_min;
   month = localtime(&stbuf.st_mtime)->tm_mon + 1;
  
   getperm(stbuf.st_mode, perm);

   printf("%s %-4s %-4s %4ld %s %2d %02d:%02d %s\n", perm, (getpwuid(stbuf.st_uid))->pw_name, (getgrgid(stbuf.st_gid))->gr_name, stbuf.st_size, monthname[month], day, hour, min, name);
   return;
}

void dirwalk(char *dir, void (*fcn)(char *))
{
   DIR *dfd;
   struct dirent *d;
   char name[MAXFILENAME];

   if((dfd = opendir(dir)) == NULL)
   {
      fprintf(stderr, "Error opening the directory %s.\n", dir);
      return;
   }

   while((d = readdir(dfd)) != NULL)
   {
      if(   strcmp(d->d_name, ".") == 0
         || strcmp(d->d_name, "..") == 0)
         continue;

      if(strlen(d->d_name) + strlen(dir) + 2 > MAXFILENAME)
      {
         fprintf(stderr, "The name %s/%s is too long.\n", dir, d->d_name);
         return;
      }

      sprintf(name, "%s/%s", dir, d->d_name);
      fcn(name);
   }

   closedir(dfd);
   return;
}
