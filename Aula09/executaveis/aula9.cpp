#include <iostream>
#include <vector>
#include <algorithm> // Para std::sort
#include <chrono>    // Para medir o tempo de execução
#include <fstream>   // Para leitura de arquivos

using namespace std;
using namespace std::chrono;

struct Item {
    int peso;
    int valor;
};

struct ResultadoMochila {
    int pesoFinal;
    int valorFinal;
    std::vector<Item> itensUsados;
};

// Função de comparação para ordenar itens pelo valor
bool comparaValor(const Item& a, const Item& b) {
    return a.valor > b.valor;
}

// Função de comparação para ordenar itens pelo peso
bool comparaPeso(const Item& a, const Item& b) {
    return a.peso < b.peso;
}

ResultadoMochila MaisAlgumaCoisa(vector<Item> itens, int capacidadeMax) {
    ResultadoMochila resultado = {0, 0, {}};
    for (const Item& item : itens) {
        if (item.peso + resultado.pesoFinal <= capacidadeMax) {
            resultado.pesoFinal += item.peso;
            resultado.valorFinal += item.valor;
            resultado.itensUsados.push_back(item);
        }
    }
    return resultado;
}

// Função para imprimir o resultado da mochila
void printResultado(const ResultadoMochila& resultado) {
    cout << "Peso total: " << resultado.pesoFinal << " Kg\n";
    cout << "Valor total: " << resultado.valorFinal << "\n";
    cout << "-----------------------\n";
}

int main() {
    vector<string> arquivos = {"entrada_valor_melhor.txt", "entrada_peso_melhor.txt"};
    for (const string& arq : arquivos) {
        ifstream arquivo("../entradas/" + arq);
        if (!arquivo) {
            cerr << "Erro ao abrir o arquivo de entrada.\n";
            return 0;
        }

        int numeroDeItens, capacidadeMax;
        arquivo >> numeroDeItens >> capacidadeMax;
        cout << "Arquivo: " << arq << "\n";
        cout << "Numero de itens: " << numeroDeItens << ", Capacidade máxima: " << capacidadeMax << " Kg\n";

        vector<Item> itens(numeroDeItens);
        for (int i = 0; i < numeroDeItens; ++i) {
            arquivo >> itens[i].peso >> itens[i].valor;
        }
        arquivo.close();

        // Ordena o vetor itens do maior para o menor (baseado no valor)
        auto inicioValor = high_resolution_clock::now(); // Início do tempo para valor
        std::sort(itens.begin(), itens.end(), comparaValor);
        ResultadoMochila resultadoValor = MaisAlgumaCoisa(itens, capacidadeMax);
        auto fimValor = high_resolution_clock::now(); // Fim do tempo para valor
        auto duracaoValor = duration_cast<nanoseconds>(fimValor - inicioValor).count();

        // Imprime o resultado da heurística de valor
        cout << "Resultado da heurística por valor:\n";
        printResultado(resultadoValor);
        cout << "Tempo de execução (valor): " << duracaoValor << " ns\n\n\n";

        // Ordena o vetor itens do mais leve para o mais pesado
        auto inicioPeso = high_resolution_clock::now(); // Início do tempo para peso
        std::sort(itens.begin(), itens.end(), comparaPeso);
        ResultadoMochila resultadoPeso = MaisAlgumaCoisa(itens, capacidadeMax);
        auto fimPeso = high_resolution_clock::now(); // Fim do tempo para peso
        auto duracaoPeso = duration_cast<nanoseconds>(fimPeso - inicioPeso).count();

        // Imprime o resultado da heurística de peso
        cout << "Resultado da heurística por peso:\n";
        printResultado(resultadoPeso);
        cout << "Tempo de execução (peso): " << duracaoPeso << " ns\n";

        cout << "==============================\n\n\n";
    }
    return 0;
}
