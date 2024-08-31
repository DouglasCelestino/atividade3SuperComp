#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

const vector<string> entradas = {"../inputs/entrada1.txt", "../inputs/entrada2.txt", "../inputs/entrada3.txt", "../inputs/entrada4.txt"};

// Função recursiva para resolver o problema da mochila
int mochila(int capacidade, const vector<int>& pesos, const vector<int>& valores, int n) {
    // Caso base: se não há mais itens ou a capacidade é zero
    if (n == 0 || capacidade == 0) {
        return 0;
    }

    // Se o peso do item n-ésimo é maior que a capacidade, não podemos incluí-lo
    if (pesos[n-1] > capacidade) {
        return mochila(capacidade, pesos, valores, n-1);
    } else {
        // Caso contrário, temos duas opções: incluir ou não o item
        int incluir = valores[n-1] + mochila(capacidade - pesos[n-1], pesos, valores, n-1);
        int nao_incluir = mochila(capacidade, pesos, valores, n-1);
        return max(incluir, nao_incluir); // Retorna a melhor das duas opções
    }
}

int main() {
    for (const string& arquivo : entradas) {
        ifstream file(arquivo); // Abra o arquivo atual

        if (!file) {
            cerr << "Erro ao abrir o arquivo: " << arquivo << endl;
            continue; // Pula para o próximo arquivo se houver erro
        }

        int n, capacidade;
        file >> n >> capacidade; // Lê o número de itens e a capacidade da mochila

        vector<int> pesos(n), valores(n);
        for (int i = 0; i < n; i++) {
            file >> pesos[i] >> valores[i]; // Lê os pesos e valores dos itens
        }

        file.close(); // Fecha o arquivo

        int valor_maximo = mochila(capacidade, pesos, valores, n); // Chama a função recursiva
        cout << "Arquivo: " << arquivo << " - O valor máximo que pode ser carregado é: " << valor_maximo << endl;
    }

    return 0;
}
