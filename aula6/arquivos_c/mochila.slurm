#!/bin/bash
#SBATCH --job-name=mochila    # Nome do job
#SBATCH --output=../output/mochila_%j.txt   # Gera um novo arquivo de saída a cada execução
#SBATCH --ntasks=1                               # Número de tarefas (apenas 1 processos)
#SBATCH --cpus-per-task=1                        # Número de threads por tarefa (apenas 1 thread por processo)
#SBATCH --mem=512MB                             # Memória total alocada por nó (512 MB)
#SBATCH --time=00:10:00                          # Tempo máximo de execução (até 10 minutos)
#SBATCH --partition=espec                       # Fila do cluster a ser utilizada

# Executa o programa usando MPI e OpenMP
./mochila