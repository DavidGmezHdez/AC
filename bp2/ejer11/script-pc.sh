#!/bin/bash
export OMP_DYNAMIC=FALSE

export OMP_NUM_THREADS=1
./pmv-OpenMP-b 5000;
./pmv-OpenMP-b 20000;

export OMP_NUM_THREADS=2
./pmv-OpenMP-b 5000;
./pmv-OpenMP-b 20000;

export OMP_NUM_THREADS=3
./pmv-OpenMP-b 5000;
./pmv-OpenMP-b 20000;

export OMP_NUM_THREADS=4
./pmv-OpenMP-b 5000;
./pmv-OpenMP-b 20000;