#!/bin/bash
# Toy simulation running all, split into soma/prox/mid/dist to run separately
#nrngui run_soma.hoc
for num in $(seq -50 50)
do
for type in soma prox midd dist
do
        var=$(printf "%0.1f\n" $(echo "scale = 1; $num/10" | bc))
        echo $var
        echo $num
        mosinit_filename=mosinit_pt_${num}.hoc
        run_filename=run_${type}_pt_${num}.hoc
        perl -p -e "s/INSERT_HERE/$var/" template_mosinit.hoc > ../$mosinit_filename
        perl -p -e "s/INSERT_HERE/$num/" run_${type}_template.hoc > ../$run_filename
        filename_runscript=runscript_${type}_pt_${num}.sh
        perl -p -e "s/INSERT_HERE/$num/ and s/TYPE/$type/" template_runscript.sh > $filename_runscript
        echo "nrngui $run_filename" >> $filename_runscript
        qsub $filename_runscript
done
done
