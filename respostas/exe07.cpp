#include <iostream>
#include <vector>

void bubbleSort(std::vector<int>& v) {
    bool trocado;
    int tamanho = v.size();
    
    for (int i = 0; i < tamanho - 1; ++i) {
        trocado = false;
        for (int j = 0; j < tamanho - i - 1; ++j) {
            if (v[j] > v[j + 1]) {
                std::swap(v[j], v[j + 1]);
                trocado = true;
            }
        }
        if (!trocado) break;
    }
}

int main() {
    using namespace std;

    vector<int> lista = {5, 4, 3, 2, 1};
    cout << "Vetor antes da ordenação: ";
    for (int num : lista) {
        cout << num << " ";
    }
    cout << endl;
    bubbleSort(lista); 
    cout << "Vetor após a ordenação: ";
    for (int num : lista) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
