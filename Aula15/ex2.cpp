#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 3) {
        if (rank == 0) {
            std::cerr << "O número de processos deve ser maior que 2 para formar um anel." << std::endl;
        }
        MPI_Finalize();
        return 1;
    }

    int mensagem = rank;  // Mensagem inicial é o rank do processo

    // Processo 0 envia uma mensagem para o próximo processo (rank 1)
    if (rank == 0) {
        MPI_Send(&mensagem, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        std::cout << "Processo " << rank << " enviou: " << mensagem << " para o processo " << rank + 1 << std::endl;

        // Recebe a mensagem do último processo (size - 1) para fechar o anel
        MPI_Recv(&mensagem, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Processo " << rank << " recebeu: " << mensagem << " do processo " << size - 1 << std::endl;
    }
    else {
        // Recebe mensagem do processo anterior
        MPI_Recv(&mensagem, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Processo " << rank << " recebeu: " << mensagem << " do processo " << rank - 1 << std::endl;

        // Envia mensagem para o próximo processo (ou para o processo 0 se for o último)
        int destino = (rank + 1) % size;
        MPI_Send(&mensagem, 1, MPI_INT, destino, 0, MPI_COMM_WORLD);
        std::cout << "Processo " << rank << " enviou: " << mensagem << " para o processo " << destino << std::endl;
    }

    MPI_Finalize();
    return 0;
}
