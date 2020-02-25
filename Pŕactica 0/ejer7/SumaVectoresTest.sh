#!/bin/bash

#Testearemos para cada longitud los tres programas

for ((i = 65536 ; i <= 67108864 ; i=i*2)); do
   echo "Tamaño: $i " ;
   ./SumaVectoresC $i ;
done
