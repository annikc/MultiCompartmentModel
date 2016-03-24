#!/bin/bash
#PBS -l nodes=1:m64g:ppn=16,walltime=12:00:00 -q sandy
#PBS -N soma_100000_m64_max

module load intel 

cd $SCRATCH/MultiVarSim
nrnivmodl
# Toy simulation running all, split into soma/prox/mid/dist to run separately
nrngui run_soma.hoc
#nrngui run_prox.hoc
#nrngui run_midd.hoc
#nrngui run_dist.hoc

