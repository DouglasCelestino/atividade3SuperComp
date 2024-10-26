#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Cada processo tem um valor exclusivo (por exemplo, seu próprio rank)
    int valor = rank + 1;  // Valor exclusivo de cada processo (1, 2, 3, ...)

    // Variável para armazenar a soma acumulada
    int soma_acumulada = 0;

    if (rank == 0) {
        // Processo 0 inicia a soma com seu valor
        soma_acumulada = valor;
        MPI_Send(&soma_acumulada, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        std::cout << "Processo " << rank << " enviou a soma: " << soma_acumulada << " para o processo " << rank + 1 << std::endl;
    } else {
        // Recebe a soma acumulada do processo anterior
        MPI_Recv(&soma_acumulada, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Processo " << rank << " recebeu a soma: " << soma_acumulada << " do processo " << rank - 1 << std::endl;

        // Soma o valor exclusivo do processo
        soma_acumulada += valor;

        // Se não for o último processo, envia a soma acumulada para o próximo processo
        if (rank < size - 1) {
            MPI_Send(&soma_acumulada, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
            std::cout << "Processo " << rank << " enviou a soma: " << soma_acumulada << " para o processo " << rank + 1 << std::endl;
        } else {
            // Último processo exibe a soma total
            std::cout << "Processo " << rank << " é o último processo. Soma total: " << soma_acumulada << std::endl;
        }
    }

    MPI_Finalize();
    return 0;
}
