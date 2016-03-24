#!/bin/bash
#Toy simulation running all, split into soma/prox/mid/dist to run separately
#nrngui run_soma.hoc
for var in -50 -25 -15 -10 -5 -4 -3 -2 -1 0 1 2 3 4 5 10 15 25 50
do
for type in soma prox midd dist
do
	mosinit_filename=mosinit_$var.hoc
	run_filename=run_${type}_${var}.hoc
	perl -p -e "s/INSERT_HERE/$var/" template_mosinit.hoc > ../$mosinit_filename
	perl -p -e "s/INSERT_HERE/$var/" run_${type}_template.hoc > ../$run_filename

	filename_runscript=runscript_${type}_${var}.sh
	perl -p -e "s/INSERT_HERE/$var/ and s/TYPE/$type/" template_runscript.sh > $filename_runscript
	echo "nrngui $run_filename" >> $filename_runscript
	qsub $filename_runscript
done
done

