#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void double_nums_referencia(vector<int>& numeros){
    for(size_t i=0; i < numeros.size(); i++){
        numeros[i] = numeros[i] * 2; 
    }
}

void double_nums_ponteiro(vector<int>* numeros){
    for(size_t i=0; i < (*numeros).size(); i++){
        (*numeros)[i] = (*numeros)[i] * 2; 
    }
}

void lerNumeros(const string& caminhoArquivo, vector<int>& numeros) {
    ifstream arquivo(caminhoArquivo); // Abre o arquivo para leitura

    if (!arquivo.is_open()) { // Verifica se o arquivo foi aberto com sucesso
        cerr << "Erro ao abrir o arquivo." << endl;
        return;
    }

    int numero;
    while (arquivo >> numero) { // Lê números inteiros do arquivo
        numeros.push_back(numero); // Adiciona cada número ao vetor
    }

    arquivo.close(); // Fecha o arquivo após a leitura
}

void escreve_arquivo(vector<int>& numeros){
    for (int numero : numeros){
        cout << numero << endl;
    }
}

int main() {
    vector<int> numeros;
    lerNumeros("entrada.txt", numeros); // Chama a função passando o caminho do arquivo e o vetor

    cout << "Referência: \n";

    double_nums_referencia(numeros);

    // Exibe os números lidos
    escreve_arquivo(numeros);

    cout << "Ponteiro: \n";

    double_nums_ponteiro(&numeros);

    // Exibe os números lidos
    escreve_arquivo(numeros);

    return 0;
}
