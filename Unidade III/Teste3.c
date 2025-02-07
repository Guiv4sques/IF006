#include <stdlib.h>
#include <stdio.h>

// Definição da estrutura da árvore binária
typedef struct No {
    int valor;
    int altura;
    struct No *esquerda, *direita;
} No;

// Função para criar um novo nó
No* novoNo(int valor, int altura) {
    No* no = (No*)malloc(sizeof(No));
    no->valor = valor;
    no->altura = altura;
    no->esquerda = no->direita = NULL;
    return no;
}

// Função para inserir um valor na árvore binária
No* inserir(No* raiz, int valor, int altura) {
    if (raiz == NULL) return novoNo(valor, altura);
    
    if (valor < raiz->valor) {
        raiz->esquerda = inserir(raiz->esquerda, valor, altura + 1);
    } else if (valor > raiz->valor) {
        raiz->direita = inserir(raiz->direita, valor, altura + 1);
    }
    
    return raiz;
}

// Função para encontrar um nó na árvore
No* encontrar(No* raiz, int valor) {
    if (!raiz || raiz->valor == valor) return raiz;
    if (valor < raiz->valor) return encontrar(raiz->esquerda, valor);
    return encontrar(raiz->direita, valor);
}

// Função para remover um nó da árvore
No* remover(No* raiz, int valor) {
    if (raiz == NULL) return NULL;
    if (valor < raiz->valor) {
        raiz->esquerda = remover(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = remover(raiz->direita, valor);
    } else {
        if (raiz->esquerda == NULL) {
            No* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
    }
    return raiz;
}

// Função para imprimir os valores da árvore em ordem com suas alturas
void imprimirEmOrdem(No* raiz) {
    if (raiz == NULL) return;
    imprimirEmOrdem(raiz->esquerda);
    printf("%d (%d) ", raiz->valor, raiz->altura);
    imprimirEmOrdem(raiz->direita);
}

int main() {
    FILE *entrada = fopen("L2Q3.in", "r");
    FILE *saida = fopen("L2Q3.out", "w");

    if (entrada == NULL || saida == NULL) {
        printf("Erro ao abrir arquivos!");
        return 0;
    }
    
    char linha[256];
    while (fgets(linha, sizeof(linha), entrada)) {
        No* raiz = NULL;
        char op;
        int valor;
        char *ptr = linha;
        
        while (sscanf(ptr, " %c %d", &op, &valor) == 2) {
            if (op == 'a') {
                raiz = inserir(raiz, valor, 0);
            } else if (op == 'r') {
                if (!encontrar(raiz, valor)) {
                    raiz = inserir(raiz, valor, 0);
                } else {
                    raiz = remover(raiz, valor);
                }
            }
            while (*ptr != ' ' && *ptr != '\0') ptr++;
            if (*ptr == ' ') ptr++;
        }
        
        imprimirEmOrdem(raiz);
        printf("\n");
    }
    
    fclose(entrada);
    return 0;
}