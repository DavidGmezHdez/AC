#include <stdio.h>
#ifdef _OPENMP
  #include <omp.h>
#endif

int main()
{
   int n = 7;
   int a[n];

   for (int i=0; i<n; i++)
      a[i] = i+1;

   #pragma omp parallel for shared(a,n) default(none)
   for (int i=0; i<n; i++)    a[i] += i;

   printf("Después de parallel for:\n");

   for (int i=0; i<n; i++)
      printf("a[%d] = %d\n",i,a[i]);
}
