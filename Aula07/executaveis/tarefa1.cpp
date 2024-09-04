#include <iostream>
#include <vector>
#include <algorithm> // Para std::shuffle
#include <random>    // Para std::default_random_engine
#include <chrono>    // Para medir o tempo de execução
#include <fstream>   // Para leitura de arquivos

struct Item {
    int peso;
    int valor;
};

std::pair<int, int> embaralharEPreencher(std::vector<Item> itens, int capacidadeMax) {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::shuffle(itens.begin(), itens.end(), eng); // Embaralha os itens

    int pesoTotal = 0;
    int valorTotal = 0;

    for (const auto& item : itens) {
        if (pesoTotal + item.peso <= capacidadeMax) {
            pesoTotal += item.peso;
            valorTotal += item.valor;
        }
    }

    return {pesoTotal, valorTotal};
}

int main() {
    std::ifstream arquivo("entrada.txt");
    if (!arquivo) {
        std::cerr << "Erro ao abrir o arquivo de entrada.\n";
        return 1;
    }

    int numeroDeItens, capacidadeMax;
    arquivo >> numeroDeItens >> capacidadeMax;

    std::vector<Item> itens(numeroDeItens);
    for (int i = 0; i < numeroDeItens; ++i) {
        arquivo >> itens[i].peso >> itens[i].valor;
    }
    arquivo.close();

    auto start = std::chrono::high_resolution_clock::now();
    auto [pesoFinal, valorFinal] = embaralharEPreencher(itens, capacidadeMax);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "Peso ocupado: " << pesoFinal << " Kg, Valor alcançado: " << valorFinal << " dinheiros, Tempo de execução: " << duration.count() << " segundos\n";

    return 0;
}
