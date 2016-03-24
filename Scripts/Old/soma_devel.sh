#!/bin/bash
#PBS -l nodes=1:ppn=8,walltime=0:15:00
#PBS -N soma_1000

module load intel 

cd $SCRATCH/MultiVarSim
nrnivmodl
# Toy simulation running all, split into soma/prox/mid/dist to run separately
nrngui run_soma.hoc
#nrngui run_prox.hoc
#nrngui run_midd.hoc
#nrngui run_dist.hoc
