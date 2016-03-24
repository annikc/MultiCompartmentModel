#!/bin/bash
#PBS -l nodes=1:m64g:ppn=16,walltime=4:00:00 -q sandy
#PBS -N STDP_calc

module load intel #gnu-parallel

cd $SCRATCH/MultiVarSim
nrnivmodl
# Feb 5: copied shortrun.hoc and modified for calc only
nrngui runSTDP_calc.hoc
