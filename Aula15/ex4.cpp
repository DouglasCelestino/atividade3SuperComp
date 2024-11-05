#include <mpi.h>
#include <iostream>
#include <cstring>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Processo 0 envia mensagens para todos os outros processos
        for (int i = 1; i < size; ++i) {
            std::string mensagem = "Mensagem para o processo " + std::to_string(i);
            MPI_Send(mensagem.c_str(), mensagem.size() + 1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
            std::cout << "Processo 0 enviou: " << mensagem << " para o processo " << i << std::endl;
        }
    } else {
        // Outros processos recebem a mensagem
        char mensagem_recebida[100];
        MPI_Recv(mensagem_recebida, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Processo " << rank << " recebeu: " << mensagem_recebida << std::endl;
    }

    MPI_Finalize();
    return 0;
}
