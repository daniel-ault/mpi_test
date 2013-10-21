#!/bin/sh
#PBS -l nodes=1:default:ppn=16
#PBS -l walltime=00:05:00
# PBS -A [Dept Code]
#PBS -N SendTest


cd $PBS_O_WORKDIR
tmpdir="/scratch/$USER/$PBS_JOBID"
/bin/mkdir -p $tmpdir
rsync -a ./ $tmpdir
cd $tmpdir

#source the module command
source /etc/profile.d/modules.sh

#load some modules
#module load openmpi

mpirun -np 'cat $PBS_NODEFILE | wc -l' send.a

cd $PBS_O_WORKDIR
rsync -a $tmpdir/ .
/bin/rm -fr $tmpdir