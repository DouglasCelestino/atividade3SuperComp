#include <iostream>
int main(){
    using namespace std;
    float num_a, num_b;
    string operacao;
    cout << "Digite o primeiro numero: "; cin >> num_a;
    cout << "Digite o segundo numero: "; cin >> num_b;
    cout << "Operação (+ para soma, - sub, * multiplicação e / para divisão): "; cin >> operacao;
    
    float resultado;
    if(operacao == "+"){
        resultado = num_a + num_b;
    } else if(operacao == "-"){
        resultado = num_a - num_b;
    } else if(operacao == "*"){
        resultado = num_a * num_b;
    } else if(operacao == "/"){
        if (num_b != 0) {
            resultado = num_a / num_b;
        } else {
            cout << "Erro: Divisão por zero não é permitida." << endl;
            return 1;
        }
    } else{
        cout << "Operação Inválida";
        return 1;
    }

    cout << "Resultado da operação: " << resultado;
}