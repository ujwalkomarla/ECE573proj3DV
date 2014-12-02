#!/bin/bash
make -f makefile.mak
i=1
while [ $i -lt 33 ]; do
	echo $i
	./distance_vector $i trial.txt 1 2
	
	let i=i+1
done
