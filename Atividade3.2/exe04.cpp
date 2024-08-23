#include <iostream>

class Vector {
public:
    // Construtor que inicializa o vetor com um tamanho específico
    Vector(int tamanho) : tam(tamanho), capacidade(tamanho), dados(new int[tamanho]) {}

    // Destrutor para liberar a memória alocada dinamicamente
    ~Vector() {
        delete[] dados;
    }

    // Método para inicializar todos os elementos do vetor com um valor específico
    void inicializa(int valor) {
        for (int i = 0; i < tam; ++i) {
            dados[i] = valor;
        }
    }

    // Método para obter o valor em um índice específico (const para garantir que não altera o objeto)
    int get(int index) const {
        if (index >= 0 && index < tam) {
            return dados[index];
        }
        throw std::out_of_range("Índice fora dos limites");
    }

    // Método para definir o valor em um índice específico
    void set(int index, int valor) {
        if (index >= 0 && index < tam) {
            dados[index] = valor;
        } else {
            throw std::out_of_range("Índice fora dos limites");
        }
    }

    // Método para inserir um valor em um índice específico, redimensionando se necessário
    void inserir(int index, int valor) {
        if (tam == capacidade) {
            redimensiona(capacidade * 2);  // Redimensiona o vetor se a capacidade estiver cheia
        }
        for (int i = tam; i > index; --i) {
            dados[i] = dados[i - 1];
        }
        dados[index] = valor;
        ++tam;
    }

    // Método para remover o valor em um índice específico
    void remover(int index) {
        for (int i = index; i < tam - 1; ++i) {
            dados[i] = dados[i + 1];
        }
        --tam;
    }

    // Método para imprimir todos os elementos do vetor
    void imprime() const {
        for (int i = 0; i < tam; ++i) {
            std::cout << dados[i] << " ";
        }
        std::cout << std::endl;
    }

    // Método para multiplicar todos os elementos do vetor por um escalar
    void multiplicarPorEscalar(int escalar) {
        for (int i = 0; i < tam; ++i) {
            dados[i] *= escalar;
        }
    }

private:
    int* dados;     // Ponteiro para os dados do vetor
    int tam;        // Número de elementos no vetor
    int capacidade; // Capacidade máxima do vetor

    // Método para redimensionar o vetor dinamicamente
    void redimensiona(int novaCapacidade) {
        int* novoArray = new int[novaCapacidade];
        for (int i = 0; i < tam; ++i) {
            novoArray[i] = dados[i];
        }
        delete[] dados;
        dados = novoArray;
        capacidade = novaCapacidade;
    }
};

int main() {
    Vector vec(5);
    vec.inicializa(2);  // Inicializa todos os elementos com o valor 2
    vec.imprime();      // Imprime: 2 2 2 2 2

    vec.set(2, 10);     // Define o elemento no índice 2 como 10
    vec.imprime();      // Imprime: 2 2 10 2 2

    vec.inserir(3, 7);  // Insere o valor 7 no índice 3
    vec.imprime();      // Imprime: 2 2 10 7 2 2

    vec.remover(1);     // Remove o valor no índice 1
    vec.imprime();      // Imprime: 2 10 7 2 2

    vec.multiplicarPorEscalar(3);  // Multiplica todos os elementos por 3
    vec.imprime();      // Imprime: 6 30 21 6 6

    return 0;
}
