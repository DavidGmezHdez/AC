#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
  #include <omp.h>
#else
   #define omp_get_thread_num() 0
#endif

int main(int argc, char **argv) { 
  int i, n=200,chunk,a[n],suma=0;
  omp_sched_t * kind;
  int * modifier;

   if(argc < 3)     {
      fprintf(stderr,"\nFalta iteraciones o chunk \n");
      exit(-1);
     }
   n = atoi(argv[1]); if (n>200) n=200; chunk = atoi(argv[2]); 

   for (i=0; i<n; i++)       a[i] = i; 
 
   #pragma omp parallel
   {
    #pragma omp single
    {
      printf("DENTRO DEL PARALLEL\n");
      printf("DIN-VAR: %d\n", omp_get_dynamic());
      omp_set_dynamic(2);
      printf("DIN-VAR MODIFICADO: %d\n", omp_get_dynamic());

      printf("NTHREADS-VAR: %d\n", omp_get_max_threads());
      omp_set_num_threads(4);
      printf("NTHREADS-VAR MODIFICADO: %d\n", omp_get_max_threads());

    
      omp_get_schedule(&kind, &modifier);
      printf("RUN-SCHED-VAR:  Kind: %d    Modifier: %d\n", kind, modifier);
      omp_set_schedule(4,4);
      omp_get_schedule(&kind, &modifier);
      printf("RUN-SCHED-VAR MODIFICADO:  Kind: %d    Modifier: %d\n", kind, modifier);
    }
   }

   #pragma omp parallel for firstprivate(suma) \
            lastprivate(suma) schedule(dynamic,chunk)
   for (i=0; i<n; i++)
   {   suma = suma + a[i];
       printf(" thread %d suma a[%d]=%d suma=%d \n",
             omp_get_thread_num(),i,a[i],suma);
   }  

    printf("FUERA DEL PARALLEL\n");
    printf("RESULTADO SUMA: %d\n", suma);
    printf("DIN-VAR: %d\n", omp_get_dynamic());
    printf("NTHREADS-VAR: %d\n", omp_get_max_threads());
    omp_get_schedule(&kind, &modifier);
    printf("RUN-SCHED-VAR:  Kind: %d    Modifier: %d\n", kind, modifier);
   return(0);
}
