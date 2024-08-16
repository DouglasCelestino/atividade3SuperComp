#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator> // Cabeçalho para istream_iterator
#include <cctype>

using namespace std;

// Função para contar palavras em uma linha
int contarPalavras(const string& linha) {
    istringstream iss(linha);
    return distance(istream_iterator<string>(iss), istream_iterator<string>());
}

// Função para normalizar uma palavra (converter para minúsculas e remover pontuações)
string normalizarPalavra(const string& palavra) {
    string resultado;
    for (char c : palavra) {
        if (isalpha(c)) {
            resultado += tolower(c);
        }
    }
    return resultado;
}

// Função para encontrar a palavra mais frequente
string palavraMaisFrequente(const map<string, int>& frequencias) {
    string maisFrequente;
    int maxFrequencia = 0;
    for (const auto& [palavra, frequencia] : frequencias) {
        if (frequencia > maxFrequencia) {
            maxFrequencia = frequencia;
            maisFrequente = palavra;
        }
    }
    return maisFrequente;
}

int main() {
    ifstream arquivoEntrada("texto.txt"); // Nome do arquivo de entrada
    ofstream arquivoSaida("estatisticas.txt"); // Nome do arquivo de saída

    if (!arquivoEntrada) {
        cerr << "Erro ao abrir o arquivo de entrada!" << endl;
        return 1;
    }
    if (!arquivoSaida) {
        cerr << "Erro ao abrir o arquivo de saída!" << endl;
        return 1;
    }

    string linha;
    int totalPalavras = 0;
    int totalLinhas = 0;
    map<string, int> frequencias;
    int totalPalavrasPorLinha = 0;

    while (getline(arquivoEntrada, linha)) {
        totalLinhas++;
        int palavrasNaLinha = contarPalavras(linha);
        totalPalavras += palavrasNaLinha;
        totalPalavrasPorLinha += palavrasNaLinha;

        istringstream iss(linha);
        string palavra;
        while (iss >> palavra) {
            palavra = normalizarPalavra(palavra);
            if (!palavra.empty()) {
                frequencias[palavra]++;
            }
        }
    }

    arquivoEntrada.close();

    double mediaPalavrasPorLinha = totalLinhas > 0 ? static_cast<double>(totalPalavras) / totalLinhas : 0;
    string palavraMaisFreq = palavraMaisFrequente(frequencias);

    // Gravar as estatísticas no arquivo de saída
    arquivoSaida << "Número total de palavras: " << totalPalavras << endl;
    arquivoSaida << "Número total de linhas: " << totalLinhas << endl;
    arquivoSaida << "Número médio de palavras por linha: " << mediaPalavrasPorLinha << endl;
    arquivoSaida << "Palavra mais frequente: " << palavraMaisFreq << endl;

    arquivoSaida.close();

    cout << "Estatísticas gravadas no arquivo estatisticas.txt" << endl;

    return 0;
}
