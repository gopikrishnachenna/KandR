/*
 * Exercise 2-10. Rewrite the function lower, which converts upper case letters
 * to lower case, with a conditional expressioninstead of if-else.
 */

int lower(int c)
{
   return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c ;
}