#include <iostream>

int main(){
    using namespace std;
    int lista [10] = {};
    int maior=0;
    for(int n=0; n<10; n++){
        int valor;
        cout << "Insira um numero: "; cin >> valor;
        lista[n] = valor;
    }

    for(int n=0; n<10; n++){
        if(maior < lista[n]){
            maior = lista[n];
        }
    }
    cout << "Maior número da lista é: " << maior;
}