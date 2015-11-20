#!/bin/bash

function run_thing() {
	num=$1
	procs=$2
	./run $num $procs
}

function run_trials() {
	itt=6
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
