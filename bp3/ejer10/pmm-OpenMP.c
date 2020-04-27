#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char **argv)  {
   double inicio, final;
   int i,j,k;

   if(argc < 2){
      printf(stderr,"Error de introducción de paŕametros: Falta el tamaño de las matrices (tienen que ser cuadradas)\n");
      exit(-1);
    }

    int tamanio = atoi(argv[1]);

    if(tamanio < 2){
    	printf(stderr, "El tamaño tiene que ser igual o superior a 2");
    	exit(-1);
    }

    double **m1, **m2, **m;

    m1 = (double**) malloc(tamanio*sizeof(double*));
    m2 = (double**) malloc(tamanio*sizeof(double*));
    m = (double**) malloc(tamanio*sizeof(double*));

    #pragma omp parallel for
    for(i=0; i<tamanio; i++){
        m1[i] = (double*) malloc(tamanio*sizeof(double));
        m2[i] = (double*) malloc(tamanio*sizeof(double));
    	m[i] = (double*) malloc(tamanio*sizeof(double));
    }

    #pragma omp parallel private(i,j,k)
    {
        #pragma omp for schedule(dynamic)
            for(i=0; i<tamanio; i++){
                for(j=0; j<tamanio; j++){
                    m1[i][j] = 3;
                    m2[i][j] = 3;
                    m[i][j] = 0;
                }
            }
        #pragma omp critical
            inicio = omp_get_wtime();

        #pragma omp for schedule(dynamic)
            for(i=0; i<tamanio; i++){
                for(j=0; j<tamanio; j++){
                    double local = 0;
                    for(k=0;k<tamanio;k++){
                        local += m1[i][j]*m2[i][j];
                    }
                    m[i][j] = local;
                }
            }
    
        #pragma omp critical
            final = omp_get_wtime() - inicio;
    }
    if(tamanio <= 8){
    	printf("Tamaño: %i\n Tiempo de ejecución: %f\n", tamanio, final);
    	for(int i=0; i<tamanio; i++) 
            for(int j=0;j<tamanio;j++)
                printf("m[%i][%i] = %f\n", i,j, m[i][j]);
    }

    else{
    	printf("Tamaño: %i\n Tiempo de ejecución: %f\n Primer elemento: %f\n Último elemento: %f\n", tamanio, final,
    	 m[0][0], m[tamanio-1][tamanio-1]);
    }

    for(int i=0; i<tamanio; i++){
    	free(m[i]);
        free(m1[i]);
        free(m2[i]);
    }

    free(m);
    free(m1);
    free(m2);

    return 0;
}

