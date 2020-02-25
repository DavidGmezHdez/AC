#!/bin/bash

#Testearemos para cada longitud los tres programas

echo "\n\nCALCULO LOCAL\n\n"
for ((i = 65536 ; i <= 67108864 ; i=i*2)); do
   echo "Tamaño Local: $i " ;
   ./SumaVectoresLocal $i ;
done

echo "\n\nCALCULO GLOBAL\n\n"
for ((i = 65536 ; i <= 67108864 ; i=i*2)); do
   echo "Tamaño Global: $i " ;
   ./SumaVectoresGlobal $i ;
done

echo "\n\nCALCULO DINAMICO \n\n"
for ((i = 65536 ; i <= 67108864 ; i=i*2)); do
   echo "Tamaño Dinamico: $i " ;
   ./SumaVectoresDinamico $i ;
done



