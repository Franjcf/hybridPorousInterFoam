#!/bin/bash
#parallel job using 16 proccesors and runs for 12 hours (max)
#SBATCH -N 1 # node count
#SBATCH --ntasks-per-node=16 #number of threads desired
#SBATCH -t 12:00:00

# Load openmpi environment
module load openmpi/gcc

srun hybridPorousInterFoam -parallel 2>&1 1>log

