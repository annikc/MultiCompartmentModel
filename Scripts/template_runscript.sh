#!/bin/bash
#PBS -l nodes=1:m64g:ppn=16,walltime=14:00:00
#PBS -q sandy
#PBS -N m64_TYPE_pt_INSERT_HERE

module load intel 

cd $SCRATCH/MultiVarSim
nrnivmodl

