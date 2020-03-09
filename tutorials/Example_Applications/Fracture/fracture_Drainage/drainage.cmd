#!/bin/bash
#parallel job using 4 proccesors and runs for 1 hour (max)
#SBATCH -N 1 # node count
#SBATCH --ntasks-per-node=28 #number of threads desired
#SBATCH -t 10:30:00
# sends mail when process begins, and
# when it ends. Make sure you define your email
#SBATCH --mail-type=begin
#SBATCH --mail-type=end
#SBATCH --mail-user=fjc2@princeton.edu

# Load openmpi environment
module load openmpi/gcc

srun hybridPorousInterFoam -parallel 2>&1 1>log

