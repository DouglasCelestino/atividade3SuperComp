#include <iostream>
#include <vector>
#include <algorithm> // Para shuffle
#include <random>    // Para default_random_engine
#include <chrono>    // Para medir o tempo de execução
#include <fstream>   // Para leitura de arquivos

using namespace std;

struct Item {
    int peso;
    int valor;
};

struct ResultadoMochila {
    int pesoFinal = 0;
    int valorFinal = 0;
    vector<Item> itensUsados;
};

// ---------------------------------------- Substitui Objeto ----------------------------------------

ResultadoMochila embaralharEPreencher(vector<Item>& itens, int capacidadeMax) {
    random_device rd;
    default_random_engine eng(rd());
    shuffle(itens.begin(), itens.end(), eng); // Embaralha os itens

    int pesoTotal = 0;
    int valorTotal = 0;
    vector<Item> itensUsados;

    for (const auto& item : itens) {
        if (pesoTotal + item.peso <= capacidadeMax) {
            pesoTotal += item.peso;
            valorTotal += item.valor;
            itensUsados.push_back(item);
        }
    }

    return {pesoTotal, valorTotal, itensUsados};
}

ResultadoMochila mochila_cheia(vector<Item>& itens, int capacidadeMax, ResultadoMochila resultado) {
    auto start = chrono::high_resolution_clock::now();

    for (const auto& item : itens) {
        if (resultado.pesoFinal + item.peso <= capacidadeMax) {
            resultado.pesoFinal += item.peso;
            resultado.valorFinal += item.valor;
            resultado.itensUsados.push_back(item);
        }
    }
    return resultado;
}

ResultadoMochila substitui_item(vector<Item>& itens, int capacidadeMax, ResultadoMochila resultado) {
    auto start = chrono::high_resolution_clock::now();

    bool melhorou = true;
    while (melhorou) {
        melhorou = false;
        for (const auto& item : itens) {
            for (size_t j = 0 ; j < resultado.itensUsados.size(); ++j) {
                int peso_atual = resultado.pesoFinal;
                int valor_atual = resultado.valorFinal;

                // Remove o item atual da mochila
                resultado.pesoFinal -= resultado.itensUsados[j].peso;
                resultado.valorFinal -= resultado.itensUsados[j].valor;

                // Verifica se o novo item cabe e melhora o valor
                if (resultado.pesoFinal + item.peso <= capacidadeMax && resultado.valorFinal + item.valor > valor_atual) {
                    resultado.pesoFinal += item.peso;
                    resultado.valorFinal += item.valor;
                    resultado.itensUsados[j] = item;  // Substitui o item
                    melhorou = true;
                    break; // Sai do loop para evitar substituições desnecessárias
                } else {
                    // Reverte a mudança se não for uma melhoria
                    resultado.pesoFinal = peso_atual;
                    resultado.valorFinal = valor_atual;
                }
            }
        }
    }
    return resultado;
}

void busca_local(vector<Item>& itens, int capacidadeMax) {
    // Fase 1: Embaralha e preenche
    ResultadoMochila resultado = embaralharEPreencher(itens, capacidadeMax);

    // Fase 2: Mochila cheia
    resultado = mochila_cheia(itens, capacidadeMax, resultado);

    // Fase 3: Substituição de item
    resultado = substitui_item(itens, capacidadeMax, resultado);
    cout << "Substitui item: - Peso ocupado: " << resultado.pesoFinal << " Kg, Valor alcancado: " << resultado.valorFinal << " dinheiros\n";
}

// ---------------------------------------- HillClimbing ----------------------------------------

vector<vector<int>> gerarVizinhos(const vector<int>& solucao) {
    vector<vector<int>> vizinhos;
    for (size_t i = 0; i < solucao.size(); ++i) {
        vector<int> novoVizinho = solucao;
        novoVizinho[i] = 1 - solucao[i]; // Alterna entre 0 e 1
        vizinhos.push_back(novoVizinho);
    }
    return vizinhos;
}


ResultadoMochila hillClimbing(vector<Item>& itens, int capacidadeMax) {
    random_device rd;
    default_random_engine eng(rd());
    uniform_int_distribution<int> dist(0, 1);  // Distribuição para gerar números entre 0 e 1
    ResultadoMochila Resultado = {0, 0, {}};

    vector<int> solucao(itens.size());
    for (int& bit : solucao) {
        bit = dist(eng);  // Inicializa a solução com valores aleatórios
    }

    // Prepara a solução inicial
    for (size_t i = 0; i < solucao.size(); ++i) {
        if (solucao[i] == 1 && (Resultado.pesoFinal + itens[i].peso <= capacidadeMax)) {
            Resultado.pesoFinal += itens[i].peso;
            Resultado.valorFinal += itens[i].valor;
            Resultado.itensUsados.push_back(itens[i]);
        }
    }
    vector<vector<int>> vizinhos = gerarVizinhos(solucao);
    for (int i = 0; i < vizinhos.size(); ++i) {
        for (const auto& vizinho : vizinhos) {
            ResultadoMochila resultadoVizinho = {0, 0, {}};
            for (size_t j = 0; j < vizinho.size(); ++j) {
                if (vizinho[j] == 1 && (resultadoVizinho.pesoFinal + itens[j].peso <= capacidadeMax)) {
                    resultadoVizinho.pesoFinal += itens[j].peso;
                    resultadoVizinho.valorFinal += itens[j].valor;
                    resultadoVizinho.itensUsados.push_back(itens[j]);
                }
            }
            if (resultadoVizinho.valorFinal > Resultado.valorFinal) {
                Resultado = resultadoVizinho;
                solucao = vizinho;
            }
        }
    }

     cout << "HillClimbing: - Peso ocupado: " << Resultado.pesoFinal << " Kg, Valor alcancado: " << Resultado.valorFinal << " dinheiros\n";
    return Resultado;
}



int main() {
    vector<string> arquivos = {"entrada1.txt", "entrada2.txt", "entrada3.txt", "entrada4.txt"};
    for(string arq : arquivos){
        ifstream arquivo("../entradas/" + arq);
        if (!arquivo) {
            cerr << "Erro ao abrir o arquivo de entrada.\n";
            return 0;
        }

        int numeroDeItens, capacidadeMax;
        arquivo >> numeroDeItens >> capacidadeMax;
        cout << "Arquivo: " << arq << "\n\n\n";
        cout << "Numero de itens: " << numeroDeItens << ", Capacidade maxima: " << capacidadeMax << " Kg\n";

        vector<Item> itens(numeroDeItens);
        for (int i = 0; i < numeroDeItens; ++i) {
            arquivo >> itens[i].peso >> itens[i].valor;
        }
        arquivo.close();

        // roda 10x busca local e hillclimbing
        for(int i = 0; i < 10; i++) {
            cout << "Rodada " << i+1 << ":\n";
            busca_local(itens, capacidadeMax);
            hillClimbing(itens, capacidadeMax);
        }         
    }
    return 0;
}
