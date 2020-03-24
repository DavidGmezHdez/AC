/* SumaVectoresC.c 
 Suma de dos vectores: v3 = v1 + v2
 
 Para compilar usar (-lrt: real time library, es posible que no sea necesario usar -lrt):  
  gcc  -O2  SumaVectores.c -o SumaVectores -lrt
  gcc  -O2 -S SumaVectores.c -lrt 

 Para ejecutar use: SumaVectoresC longitud
    
*/ 

#include <stdlib.h> // biblioteca con funciones atoi(), malloc() y free()
#include <stdio.h>  // biblioteca donde se encuentra la función printf()
#include <time.h> // biblioteca donde se encuentra la función clock_gettime() 
#include <omp.h>

//Sólo puede estar definida una de las tres constantes VECTOR_ (sólo uno de los ... 
//tres defines siguientes puede estar descomentado):
//#define VECTOR_LOCAL  // descomentar para que los vectores sean variables ...
      // locales (si se supera el tamaño de la pila se ...
      // generará el error "Violación de Segmento")
#define VECTOR_GLOBAL // descomentar para que los vectores sean variables ...
      // globales (su longitud no estará limitada por el ...
      // tamaño de la pila del programa)
//#define VECTOR_DYNAMIC  // descomentar para que los vectores sean variables ...
      // dinámicas (memoria reutilizable durante la ejecución)

#ifdef VECTOR_GLOBAL
#define MAX 33554432  //=2^25
   
double v1[MAX], v2[MAX], v3[MAX]; 
#endif
int main(int argc, char** argv){ 

  double tiempo1, tiempo2;

  //Leer argumento de entrada (nº de componentes del vector)
  if (argc<2){  
    printf("Faltan nº componentes del vector\n");
    exit(-1);
  }
  
  unsigned int N = atoi(argv[1]); // Máximo N =2^32-1=4294967295 (sizeof(unsigned int) = 4 B)
  printf("Tamaño Vectores:%u (%u B)\n",N, sizeof(unsigned int)); 
  #ifdef VECTOR_LOCAL
  double v1[N], v2[N], v3[N];   // Tamaño variable local en tiempo de ejecución ...
        // disponible en C a partir de C99 
  #endif
  #ifdef VECTOR_GLOBAL
  if (N>MAX) N=MAX;
  #endif
  #ifdef VECTOR_DYNAMIC
  double *v1, *v2, *v3;
  v1 = (double*) malloc(N*sizeof(double));// malloc necesita el tamaño en bytes
  v2 = (double*) malloc(N*sizeof(double));
  v3 = (double*) malloc(N*sizeof(double));
  if ((v1 == NULL) || (v2 == NULL) || (v2 == NULL)) { 
    printf("No hay suficiente espacio para los vectores \n");
    exit(-2);
  }
  #endif

  //Inicialializamos los vectores dividiendo las tareas entre 4
  #pragma omp parallel sections
  {

    #pragma omp section
      for(int i=0; i<N/2; i++){
        v1[i] = N*0.1+i*0.1; v2[i] = N*0.1-i*0.1;
      }

    #pragma omp section
      for(int i=N/2; i<N; i++){
        v1[i] = N*0.1+i*0.1; v2[i] = N*0.1-i*0.1;
    }
      
  }
  tiempo1 = omp_get_wtime();
  //Realizamos la suma de los vectores dividiendo las tareas entre 4
  #pragma omp parallel sections
  {
    #pragma omp section
      for(int i=0; i<N/2; i++) 
        v3[i] = v1[i] + v2[i];

    #pragma omp section
      for(int i=N/2; i<N; i++) 
        v3[i] = v1[i] + v2[i];

  }
  tiempo2 = omp_get_wtime() - tiempo1;

  //Imprimimos los resultados
  if (N<10) {
  printf("Tiempo:%11.9f\t / Tamaño Vectores:%u\n",tiempo2,N); 
  for(int i=0; i<N; i++) 
    printf("/ V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n",
           i,i,i,v1[i],v2[i],v3[i]); 
  }
  else
    printf("Tiempo:%11.9f\t / Tamaño Vectores:%u\t/ V1[0]+V2[0]=V3[0](%8.6f+%8.6f=%8.6f) / / V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n",
           tiempo2,N,v1[0],v2[0],v3[0],N-1,N-1,N-1,v1[N-1],v2[N-1],v3[N-1]); 
 

  #ifdef VECTOR_DYNAMIC
  free(v1); // libera el espacio reservado para v1
  free(v2); // libera el espacio reservado para v2
  free(v3); // libera el espacio reservado para v3
  #endif
  return 0; 
}