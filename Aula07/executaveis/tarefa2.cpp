#include <iostream>
#include <vector>
#include <random>    // Para std::default_random_engine e std::uniform_real_distribution
#include <chrono>    // Para medir o tempo de execução
#include <fstream>   // Para leitura de arquivos

struct Item {
    int peso;
    int valor;
};

std::pair<int, int> selecaoAleatoriaProbabilistica(std::vector<Item>& itens, int capacidadeMax, double limiar) {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);  // Distribuição para gerar números entre 0 e 1

    int pesoTotal = 0;
    int valorTotal = 0;

    for (const auto& item : itens) {
        double probabilidade = dist(eng);  // Gera um número aleatório entre 0 e 1
        if (probabilidade > limiar && pesoTotal + item.peso <= capacidadeMax) {
            pesoTotal += item.peso;
            valorTotal += item.valor;
        }
    }

    return {pesoTotal, valorTotal};
}

int main() {
    std::ifstream arquivo("../entradas/entrada1.txt");
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

    double limiar = 0.5;  // Defina o valor limiar como 0.5 (pode ser ajustado)
    
    auto start = std::chrono::high_resolution_clock::now();
    auto [pesoFinal, valorFinal] = selecaoAleatoriaProbabilistica(itens, capacidadeMax, limiar);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "Peso ocupado: " << pesoFinal << " Kg, Valor alcançado: " << valorFinal << " dinheiros, Tempo de execução: " << duration.count() << " segundos\n";

    return 0;
}
