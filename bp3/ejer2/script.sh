#!/bin/bash
export OMP_NUM_THREADS=4


	echo "Schedule con STATIC"
	echo "CHUNK = 1"
	./schedule-clause 1
	echo "CHUNK = 2"
	./schedule-clause 2
	echo "CHUNK = 4"
	./schedule-clause 4

	echo "Schedule con DYNAMIC"
	echo "CHUNK = 1"
	./scheduled-clause 1
	echo "CHUNK = 2"
	./scheduled-clause 2
	echo "CHUNK = 4"
	./scheduled-clause 4

	echo "Schedule con GUIDED"
	echo "CHUNK = 1"
	./scheduleg-clause 1
	echo "CHUNK = 2"
	./scheduleg-clause 2
	echo "CHUNK = 4"
	./scheduleg-clause 4