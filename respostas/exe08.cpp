#include <iostream>

int main(){
    using namespace std;
    int matriz[3][3];
    int n=1;
    int entrada;
    int soma = 0;
    cout << "Insira 9 números para preencher a matriz 3x3\n";
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cout << "Valor " << n << ":"; cin >> entrada;
            matriz[i][j] = entrada;
            n++;
        }        
    }
    for(int i=0;i<3;i++){
        soma += matriz[i][i];
    }
    cout << "\nSoma dos elementos da diagonal principal: " << soma << endl;
}