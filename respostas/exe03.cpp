#include <iostream>
int main(){
    using namespace std;
    int num;
    cout << "Informe um número: "; cin >> num;
    if (num <= 1){
        cout << "false";
        return 0;
    } else if(num == 2){
        cout << "true"; 
        return 0;
    } else if((num % 2) == 0){
        cout << "false"; 
        return 0;
    }
    for(int n=3; n < num; n+=2){
        if((num % n) == 0){
            cout << "false"; 
            return 0;
        }
    }
    cout << "true";
}