#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Função para exibir o menu
void exibirMenu() {
    cout << "\nSistema de Controle de Estoque\n";
    cout << "1. Adicionar item\n";
    cout << "2. Remover item\n";
    cout << "3. Visualizar estoque\n";
    cout << "4. Sair\n";
    cout << "Escolha uma opção: ";
}

// Função para adicionar um item ao estoque
void adicionarItem(vector<string>& estoque) {
    string item;
    cout << "Digite o nome do item a ser adicionado: ";
    cin.ignore();
    getline(cin, item);
    estoque.push_back(item);
    cout << "Item adicionado com sucesso!" << endl;
}

// Função para remover um item do estoque
void removerItem(vector<string>& estoque) {
    string item;
    cout << "Digite o nome do item a ser removido: ";
    cin.ignore();
    getline(cin, item);

    auto it = find(estoque.begin(), estoque.end(), item);
    if (it != estoque.end()) {
        estoque.erase(it);
        cout << "Item removido com sucesso!" << endl;
    } else {
        cout << "Item não encontrado no estoque!" << endl;
    }
}


void visualizarEstoque(const vector<string>& estoque) {
    if (estoque.empty()) {
        cout << "O estoque está vazio." << endl;
    } else {
        cout << "Itens no estoque:" << endl;
        for (const auto& item : estoque) {
            cout << "- " << item << endl;
        }
    }
}

int main() {
    vector<string> estoque;
    int opcao;

    do {
        exibirMenu();
        cin >> opcao;

        switch (opcao) {
            case 1:
                adicionarItem(estoque);
                break;
            case 2:
                removerItem(estoque);
                break;
            case 3:
                visualizarEstoque(estoque);
                break;
            case 4:
                cout << "Saindo do sistema..." << endl;
                break;
            default:
                cout << "Opção inválida. Tente novamente." << endl;
        }
    } while (opcao != 4);

    return 0;
}
