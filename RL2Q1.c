#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 10000

// Definindo a estrutura para o nó da árvore binária
typedef struct no {
    int chave;
    struct no *left;
    struct no *right;
} No;

// Definindo a estrutura para a root da árvore
typedef struct {
    No *root;
} Arvore;

// Função para criar uma nova árvore
Arvore *criarArvore() {
    Arvore *novaArvore = malloc(sizeof(Arvore));
    novaArvore->root = NULL;
    return novaArvore;
}

// Função para inserir um valor na árvore, retornando a altura do nó inserido
int inserirValor(Arvore *arvore, int chave) {
    No *novoNo = malloc(sizeof(No));
    novoNo->chave = chave;
    novoNo->left = NULL;
    novoNo->right = NULL;

    if (arvore->root == NULL) {
        arvore->root = novoNo;
        return 0;
    }

    No *noAtual = arvore->root;
    int altura = 0;
    
    while (1) {
        altura++;
        if (chave >= noAtual->chave) {
            if (noAtual->right != NULL)
                noAtual = noAtual->right;
            else {
                noAtual->right = novoNo;
                return altura;
            }
        } else {
            if (noAtual->left != NULL)
                noAtual = noAtual->left;
            else {
                noAtual->left = novoNo;
                return altura;
            }
        }
    }
}

// Função para encontrar o maior valor na árvore
int buscarMaiorValor(Arvore *arvore) {
    if (arvore->root == NULL)
        return -1;

    No *noAtual = arvore->root;
    while (noAtual->right)
        noAtual = noAtual->right;

    return noAtual->chave;
}

// Função para calcular a altura do maior valor na árvore
int calcularAlturaMaiorValor(Arvore *arvore) {
    if (arvore->root == NULL)
        return -1;

    No *noAtual = arvore->root;
    int altura = 0;
    while (noAtual->right) {
        altura++;
        noAtual = noAtual->right;
    }

    return altura;
}

// Função para encontrar o predecessor do maior valor na árvore
int encontrarPredecessorMaiorValor(Arvore *arvore) {
    No *noAtual = arvore->root;
    No *predecessor = arvore->root;

    if (predecessor->right)
        predecessor = predecessor->right;

    while (predecessor->right) {
        predecessor = predecessor->right;
        noAtual = noAtual->right;
    }

    return noAtual->chave;
}

// Função para ler a entrada e gerar a saída
int main() {
    system("clear||cls");
    
    FILE *entrada;
    FILE *saida;

    char linha[TAM];
    char separador[] = " ";
    char *token;

    entrada = fopen("L2Q1.in", "r");
    saida = fopen("L2Q1.out", "w");

    if (entrada == NULL /*|| saida == NULL*/) {
        printf("Erro ao abrir arquivos!");
        return 0;
    }

    while (fgets(linha, TAM, entrada)) {
        Arvore *arvore = criarArvore();
        token = strtok(linha, separador);

        // Inserir valores na árvore e imprimir a altura
        int primeiroValor = 1;
        while (token != NULL) {
            int altura = inserirValor(arvore, atoi(token));

            if (primeiroValor) {
                fprintf(saida, "%d", altura);
                primeiroValor = 0;
            } else {
                fprintf(saida, " %d", altura);
            }

            token = strtok(NULL, separador);
        }

        // Calcular e imprimir o maior valor, sua altura e o predecessor
        int maiorValor = buscarMaiorValor(arvore);
        int alturaMaiorValor = calcularAlturaMaiorValor(arvore);
        int predecessorMaiorValor = encontrarPredecessorMaiorValor(arvore);

        fprintf(saida, " max %d", maiorValor);
        fprintf(saida, " alt %d", alturaMaiorValor);

        if (predecessorMaiorValor != arvore->root->chave)
            fprintf(saida, " pred %d", predecessorMaiorValor);
        else
            fprintf(saida, " pred NaN");

        fprintf(saida, "\n");
    }

    fclose(entrada);
    fclose(saida);
    return 0;
}