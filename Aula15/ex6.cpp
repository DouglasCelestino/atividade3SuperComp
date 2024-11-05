#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int mensagem = 0; // Mensagem inicial

    if (rank == 0) {
        // Processo 0 envia e recebe mensagens alternadamente com cada outro processo
        for (int i = 1; i < size; ++i) {
            // Envia uma mensagem para o processo i
            mensagem = i;  // A mensagem é apenas o número do processo de destino
            MPI_Send(&mensagem, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            std::cout << "Processo 0 enviou a mensagem " << mensagem << " para o processo " << i << std::endl;

            // Recebe uma mensagem de volta do processo i
            MPI_Recv(&mensagem, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            std::cout << "Processo 0 recebeu a mensagem de volta do processo " << i << std::endl;
        }
    } else {
        // Outros processos recebem uma mensagem do processo 0 e enviam de volta
        MPI_Recv(&mensagem, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Processo " << rank << " recebeu a mensagem " << mensagem << " do processo 0" << std::endl;

        // Envia uma mensagem de volta para o processo 0
        MPI_Send(&mensagem, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        std::cout << "Processo " << rank << " enviou a mensagem de volta para o processo 0" << std::endl;
    }

    MPI_Finalize();
    return 0;
}
