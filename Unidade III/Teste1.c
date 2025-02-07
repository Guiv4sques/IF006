#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 10000

// Definindo a estrutura para o nó da árvore binária
typedef struct no {
    int chave;
    struct no *esquerda;
    struct no *direita;
} No;

// Definindo a estrutura para a raiz da árvore
typedef struct {
    No *raiz;
} Arvore;

// Função para criar uma nova árvore
Arvore *criarArvore() {
    Arvore *novaArvore = malloc(sizeof(Arvore));
    novaArvore->raiz = NULL;
    return novaArvore;
}

// Função para inserir um valor na árvore, retornando a altura do nó inserido
int inserirValor(Arvore *arvore, int chave) {
    No *novoNo = malloc(sizeof(No));
    novoNo->chave = chave;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;

    if (arvore->raiz == NULL) {
        arvore->raiz = novoNo;
        return 0;
    }

    No *noAtual = arvore->raiz;
    int altura = 0;
    
    while (1) {
        altura++;
        if (chave >= noAtual->chave) {
            if (noAtual->direita != NULL)
                noAtual = noAtual->direita;
            else {
                noAtual->direita = novoNo;
                return altura;
            }
        } else {
            if (noAtual->esquerda != NULL)
                noAtual = noAtual->esquerda;
            else {
                noAtual->esquerda = novoNo;
                return altura;
            }
        }
    }
}

// Função para encontrar o maior valor na árvore
int buscarMaiorValor(Arvore *arvore) {
    if (arvore->raiz == NULL)
        return -1;

    No *noAtual = arvore->raiz;
    while (noAtual->direita)
        noAtual = noAtual->direita;

    return noAtual->chave;
}

// Função para calcular a altura do maior valor na árvore
int calcularAlturaMaiorValor(Arvore *arvore) {
    if (arvore->raiz == NULL)
        return -1;

    No *noAtual = arvore->raiz;
    int altura = 0;
    while (noAtual->direita) {
        altura++;
        noAtual = noAtual->direita;
    }

    return altura;
}

// Função para encontrar o predecessor do maior valor na árvore
int encontrarPredecessorMaiorValor(Arvore *arvore) {
    No *noAtual = arvore->raiz;
    No *predecessor = arvore->raiz;

    if (predecessor->direita)
        predecessor = predecessor->direita;

    while (predecessor->direita) {
        predecessor = predecessor->direita;
        noAtual = noAtual->direita;
    }

    return noAtual->chave;
}

// Função para ler a entrada e gerar a saída
int main() {
    FILE *entrada;
    FILE *saida;

    char linha[TAM];
    char separador[] = " ";
    char *token;

    entrada = fopen("L2Q1.in", "r");
    saida = fopen("L2Q1.out", "w");

    if (entrada == NULL || saida == NULL) {
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

        if (predecessorMaiorValor != arvore->raiz->chave)
            fprintf(saida, " pred %d", predecessorMaiorValor);
        else
            fprintf(saida, " pred NaN");

        fprintf(saida, "\n");
    }

    fclose(entrada);
    fclose(saida);
    return 0;
}
