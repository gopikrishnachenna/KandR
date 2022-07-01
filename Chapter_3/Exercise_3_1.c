/*
 * Exercise 3-1. Our binary search makes two tests inside the loop, when one
 * would suffice (at the price of more tests outside). Write a version with only one
 * test inside the loop and measure the difference in run-time.
 */

#include <stdio.h>

int binsearch(int x, int v[], int n)
{
   int low;
   int mid;
   int high;

   low = 0;
   high = n - 1;
   while(low <= high)
   {
      mid = (low + high)/2;
      if(x < v[mid])
         high = mid - 1;
      else if(x > v[mid])
         low = mid + 1;
      else
         return mid;
   }
   return -1;
}

int mybinsearch(int x, int v[], int n)
{
   int low;
   int mid;
   int high;

   low = 0;
   high = n - 1;
   while(low < high)
   {
      mid = (low + high)/2;
      if(x <= v[mid])
         high = mid;
      else
         low = mid + 1;
   }

   /* low and high are now equal. The value should either be equal to that value.
    * Or the value is not present 
    */
   if(x == v[low])
      return low;
   else
      return -1;
}

main()
{
   int arr[9] = {1, 2, 3, 4, 5, 9, 15, 34, 96};
   int s = 96;

   printf("Official answer = %d\n", binsearch(s, arr, 10));
   printf("Expected answer = %d\n", mybinsearch(s, arr, 10));
}
