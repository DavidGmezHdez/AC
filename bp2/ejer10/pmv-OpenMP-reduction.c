#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char **argv)  {
   double inicio, final;
   int i,j;
   double local = 0;

   if(argc < 2){
      printf(stderr,"Error de introducción de paŕametros: Falta el tamaño de la matriz (tiene que ser cuadrada)\n");
      exit(-1);
    }

    int tamanio = atoi(argv[1]);

    if(tamanio < 2){
    	printf(stderr, "El tamaño tiene que ser igual o superior a 2");
    	exit(-1);
    }

    double *v1, *v2, **m;

    v1 = (double*) malloc(tamanio*sizeof(double));
    v2 = (double*) malloc(tamanio*sizeof(double));
    m = (double**) malloc(tamanio*sizeof(double*));

    for(i=0; i<tamanio; i++){
    	m[i] = (double*) malloc(tamanio*sizeof(double));
    }

#pragma omp parallel private(i)
{
    #pragma omp for private(j) 
    for(i=0; i<tamanio; i++){
        for(j=0; j<tamanio; j++){
            m[i][j] = 2;
        }
    }
    #pragma omp for
    for(i=0; i<tamanio; i++){
        v1[i] = 1;
        v2[i] = 0;
    }

    
    #pragma omp critical
        inicio = omp_get_wtime();
    
    
    for(i=0; i<tamanio; i++){
        #pragma omp for reduction(+:local) 
        for(j=0; j<tamanio; j++){
            local = local + (m[i][j]*v1[j]);
        }

        #pragma omp single
        {
            v2[i] = local;
            local = 0; 
        }
    }
}

    final = omp_get_wtime() - inicio;
    


    if(tamanio <= 8){
    	printf("Tamaño: %i\n Tiempo de ejecución: %f\n", tamanio, final);

    	for(i=0; i<tamanio; i++) printf("v2[%i] = %f\n", i, v2[i]);
    }

    else{
    	printf("Tamaño: %i\n Tiempo de ejecución: %f\n Primer elemento: %f\n Último elemento: %f\n", tamanio, final,
    	 v2[0], v2[tamanio-1]);
    }

    free(v1);
    free(v2);

    for(i=0; i<tamanio; i++){
    	free(m[i]);
    }

    free(m);

    return 0;
}

