#!/bin/bash

#mpiexec -machinefile ~/machinefile.txt -n 2 ~/Code/cs483-pa3/run 17 13 23 1 1000000
#mpiexec -machinefile ~/machinefile.txt -n 4 ~/Code/cs483-pa3/run 17 13 23 1 1000000
#mpiexec -machinefile ~/machinefile.txt -n 8 ~/Code/cs483-pa3/run 17 13 23 1 1000000
#mpiexec -machinefile ~/machinefile.txt -n 16 ~/Code/cs483-pa3/run 17 13 23 1 1000000

function run_thing() {
	num=$1
	procs=$2
	./run $num $procs
}

function run_trials() {
	itt=7
	nproc=1
	n=33554432
	for i in `seq $itt`
	do
		run_thing $n $nproc
		n=`expr $n \* 2`
		nproc=`expr $nproc \* 2`
	done
}

run_trials
