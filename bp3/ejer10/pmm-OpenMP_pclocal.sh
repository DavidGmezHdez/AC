#!/bin/bash
export OMP_DYNAMIC=FALSE

for ((i=1;i<=4;i++))
do 
	export OMP_NUM_THREADS=$i
	echo "Número hebras $i"
 	./pmm-OpenMP 100
done

for ((i=1;i<=4;i++))
do 
	export OMP_NUM_THREADS=$i
	echo "Número hebras $i"
 	./pmm-OpenMP 1500
done


