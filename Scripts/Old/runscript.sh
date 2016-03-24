#!/bin/bash
#PBS -l nodes=1:m256g:ppn=16,walltime=2:00:00 -q sandy
#PBS -N STDP_run

module load intel

cd $PBS_0_WORKDIR
cd $SCRATCH/MultiVarSim

nrnivmodl
nrngui runSTDP_ecl.hoc
nrngui runSTDP_membp.hoc
nrngui runSTDP_calc.hoc
nrngui runSTDP_kin.hoc
nrngui runSTDP_phos.hoc
