#!/bin/bash
#parallel job using 28 proccesors and runs for 10.5 hours (max)
#SBATCH -N 1 # node count
#SBATCH --ntasks-per-node=28 #number of threads desired
#SBATCH -t 10:30:00

# Load openmpi environment
module load openmpi/gcc

srun hybridPorousInterFoam -parallel 2>&1 1>log

