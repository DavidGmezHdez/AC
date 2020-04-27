#!/bin/bash
export OMP_DYNAMIC=FALSE
#Todos los scripts que se hagan para atcgrid deben incluir lo siguiente:
#PBS -N suma
#Se asigna al trabajo la cola ac
#PBS -q ac   
#Se imprime información del trabajo usando variables de entorno de PBS

echo "Id. usuario del trabajo: $PBS_O_LOGNAME"
echo "Id. del trabajo: $PBS_JOBID"
echo "Nombre  del trabajo especificado por usuario: $PBS_JOBNAME"
echo "Nodo que ejecuta qsub: $PBS_O_HOST"
echo "Directorio en el que se ha ejecutado qsub: $PBS_O_WORKDIR"
echo "Cola: $PBS_QUEUE"
echo "Nodos asignados al trabajo:" 
cat $PBS_NODEFILE

# FIN del trozo que deben incluir todos los scripts

echo "TAMAÑO 100"
for ((i=1;i<=12;i++))
do 
	export OMP_NUM_THREADS=$i
	echo "Número hebras $i"
 	srun -p ac ./pmm-OpenMP 100
done

echo "TAMAÑO 1500"
for ((i=1;i<=12;i++))
do 
	export OMP_NUM_THREADS=$i
	echo "Número hebras $i"
 	srun -p ac ./pmm-OpenMP 1500
done

