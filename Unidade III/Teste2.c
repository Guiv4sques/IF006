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

// Função para inserir um valor na árvore binária sem duplicatas
No* inserir(No* raiz, int valor, int altura) {
    if (raiz == NULL) return novoNo(valor, altura);
    
    if (valor < raiz->valor) {
        raiz->esquerda = inserir(raiz->esquerda, valor, altura + 1);
    } else if (valor > raiz->valor) {
        raiz->direita = inserir(raiz->direita, valor, altura + 1);
    }
    
    return raiz;
}

// Função para calcular a diferença entre a soma dos nós à direita e à esquerda
int calcularDiferenca(No* raiz) {
    if (!raiz) return 0;
    
    int somaEsquerda = 0, somaDireita = 0;
    
    if (raiz->esquerda) somaEsquerda = calcularDiferenca(raiz->esquerda) + raiz->esquerda->valor;
    if (raiz->direita) somaDireita = calcularDiferenca(raiz->direita) + raiz->direita->valor;
    
    return somaDireita - somaEsquerda;
}

// Função para imprimir os valores da árvore em ordem com suas diferenças
void imprimirEmOrdem(No* raiz) {
    if (raiz == NULL) return;
    imprimirEmOrdem(raiz->esquerda);
    printf("%d (%d) ", raiz->valor, calcularDiferenca(raiz));
    imprimirEmOrdem(raiz->direita);
}

int main() {
    FILE *entrada = fopen("L2Q2.in", "r");
    FILE *saida = fopen("L2Q2.out", "w");

    if (entrada == NULL || saida == NULL) {
        printf("Erro ao abrir arquivos!");
        return 0;
    }
    
    char linha[256];
    while (fgets(linha, sizeof(linha), entrada)) {
        No* raiz = NULL;
        int valor;
        char *ptr = linha;
        
        while (sscanf(ptr, "%d", &valor) == 1) {
            raiz = inserir(raiz, valor, 0);
            while (*ptr != ' ' && *ptr != '\0') ptr++; // Avança para o próximo número
            if (*ptr == ' ') ptr++; // Pula espaço
        }
        
        imprimirEmOrdem(raiz);
        printf("\n");
    }
    
    fclose(entrada);
    return 0;
}