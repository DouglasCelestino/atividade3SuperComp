#include <iostream>

int main(){
    using namespace std;
    string palavra;
    string palavra_invertida = "";
    cout << "Digite uma palavra: "; cin >> palavra;
    for(int n=palavra.size() - 1; n >= 0; n--){
        palavra_invertida += palavra[n];
    }
    if(palavra == palavra_invertida){
        cout << "A palavra digitada é um palíndromo";
    } else{
        cout << "A palavra digitada não é um palíndromo";
    }
}