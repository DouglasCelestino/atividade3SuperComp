#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int mensagem = 0; // Mensagem inicial

    if (rank == 0) {
        // Processo 0 envia a mensagem inicial para o processo 1
        mensagem = 100; // Valor da mensagem a ser transmitida
        MPI_Send(&mensagem, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        std::cout << "Processo " << rank << " enviou: " << mensagem << " para o processo " << rank + 1 << std::endl;
    } else {
        // Cada processo recebe a mensagem do anterior
        MPI_Recv(&mensagem, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Processo " << rank << " recebeu: " << mensagem << " do processo " << rank - 1 << std::endl;

        // Se não for o último processo, envia a mensagem para o próximo
        if (rank < size - 1) {
            MPI_Send(&mensagem, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
            std::cout << "Processo " << rank << " enviou: " << mensagem << " para o processo " << rank + 1 << std::endl;
        } else {
            // Último processo exibe a mensagem recebida
            std::cout << "Processo " << rank << " é o último processo. Mensagem recebida: " << mensagem << std::endl;
        }
    }

    MPI_Finalize();
    return 0;
}
