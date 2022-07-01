Exercise 2-2.  Write a loop equivalent to the for loop above without using && or ||.

For loop :

for(i=O; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)

for(i = 0; i < lim - 1; ++i)
{
   c = getchar();
   if(c == '\n')
      break;
   if(c == EOF)
      break;
   ....
}
