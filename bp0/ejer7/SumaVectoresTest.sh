#!/bin/bash

#Testearemos para cada longitud los tres programas

printf "\n\nCALCULO LOCAL\n\n"
for ((i = 65536 ; i <= 67108864 ; i=i*2)); do
   echo "Tamaño Local: $i " ;
   ./SumaVectoresLocal $i ;
done

printf "\n\nCALCULO GLOBAL\n\n"
for ((i = 65536 ; i <= 67108864 ; i=i*2)); do
   echo "Tamaño Global: $i " ;
   ./SumaVectoresGlobal $i ;
done

printf "\n\nCALCULO DINAMICO \n\n"
for ((i = 65536 ; i <= 67108864 ; i=i*2)); do
   echo "Tamaño Dinamico: $i " ;
   ./SumaVectoresDinamico $i ;
done



