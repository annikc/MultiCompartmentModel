#!/bin/bash
#PBS -l nodes=1:m64g:ppn=16,walltime=14:00:00 -q sandy
#PBS -N shortrun1000_m64

module load intel

cd $SCRATCH/MultiVarSim

nrnivmodl
# To run short (100ms) simulations with samp freq of 2000, see how long it takes to run through
nrngui runSTDP_short.hoc
