#include <iostream>

int main(){
    using namespace std;
    int lista [5] = {};
    int soma=0;
    for(int n=0; n<5; n++){
        int valor;
        cout << "Insira um numero: "; cin >> valor;
        lista[n] = valor;
    }

    for(int n=0; n<5; n++){
        soma += lista[n];
    }
    cout << "Soma dos resultados = " << soma;
}