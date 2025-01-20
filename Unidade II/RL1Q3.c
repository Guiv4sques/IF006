//Dupla: Guilherme Cauê Andrade Vasques (20241160036), Papai do Céu;
#include <stdlib.h>
#include <stdio.h>

// Estruturas para listas ligadas
typedef struct NodoCircular {
    float valor;
    struct NodoCircular *prox;
} NodoCircular;

typedef struct NodoDuplo {
    int chave;
    NodoCircular *lista;
    struct NodoDuplo *prox;
    struct NodoDuplo *ant;
} NodoDuplo;

// Função para criar um nodo da lista circular
NodoCircular* criar_nodo_circular(float valor) {
    NodoCircular *novo = (NodoCircular*)malloc(sizeof(NodoCircular));
    novo->valor = valor;
    novo->prox = novo; // Circular
    return novo;
}

// Função para inserir um valor na lista circular de forma ordenada
void inserir_ordenado_circular(NodoCircular **cabeca, float valor) {
    NodoCircular *novo = criar_nodo_circular(valor);

    if (*cabeca == NULL) {
        *cabeca = novo;
        return;
    }

    NodoCircular *atual = *cabeca;
    NodoCircular *anterior = NULL;

    do {
        if (atual->valor >= valor) break;
        anterior = atual;
        atual = atual->prox;
    } while (atual != *cabeca);

    if (anterior == NULL) {
        // Inserção no início
        novo->prox = *cabeca;
        NodoCircular *ultimo = *cabeca;
        while (ultimo->prox != *cabeca) {
            ultimo = ultimo->prox;
        }
        ultimo->prox = novo;
        *cabeca = novo;
    } else {
        // Inserção no meio ou fim
        anterior->prox = novo;
        novo->prox = atual;
    }
}

// Função para criar um nodo da lista duplamente ligada
NodoDuplo* criar_nodo_duplo(int chave) {
    NodoDuplo *novo = (NodoDuplo*)malloc(sizeof(NodoDuplo));
    novo->chave = chave;
    novo->lista = NULL;
    novo->prox = NULL;
    novo->ant = NULL;
    return novo;
}

// Função para inserir um nodo na lista duplamente ligada de forma ordenada
void inserir_ordenado_duplo(NodoDuplo **cabeca, int chave) {
    NodoDuplo *novo = criar_nodo_duplo(chave);

    if (*cabeca == NULL) {
        *cabeca = novo;
        return;
    }

    NodoDuplo *atual = *cabeca;
    NodoDuplo *anterior = NULL;

    while (atual != NULL && atual->chave < chave) {
        anterior = atual;
        atual = atual->prox;
    }

    if (anterior == NULL) {
        // Inserção no início
        novo->prox = *cabeca;
        (*cabeca)->ant = novo;
        *cabeca = novo;
    } else {
        // Inserção no meio ou fim
        novo->prox = atual;
        novo->ant = anterior;
        anterior->prox = novo;
        if (atual != NULL) {
            atual->ant = novo;
        }
    }
}

// Função para imprimir a lista duplamente ligada e suas listas circulares
void imprimir_lista(NodoDuplo *cabeca) {
    NodoDuplo *atual = cabeca;
    printf("[");

    while (atual != NULL) {
        printf("%d(", atual->chave);

        NodoCircular *circular = atual->lista;
        if (circular != NULL) {
            NodoCircular *inicio = circular;
            do {
                printf("%.2f", circular->valor);
                circular = circular->prox;
                if (circular != inicio) printf("->");
            } while (circular != inicio);
        }

        printf(")");
        if (atual->prox != NULL) printf("->");
        atual = atual->prox;
    }

    printf("]\n");
}

int main() {
    NodoDuplo *lista_dupla = NULL;

    // Entrada
    int chaves[] = {10, 9, 6, 4};
    float valores[][8] = {
        {4.11, 10.1, 6.88, 4.99, 9.3, 9.2, 6.15, 4.33},
    };
    int tamanho_chaves = sizeof(chaves) / sizeof(chaves[0]);
    int tamanho_valores = sizeof(valores[0]) / sizeof(valores[0][0]);

    // Inserir chaves na lista duplamente ligada
    for (int i = 0; i < tamanho_chaves; i++) {
        inserir_ordenado_duplo(&lista_dupla, chaves[i]);
    }

    // Associar listas circulares
    NodoDuplo *atual = lista_dupla;
    for (int i = 0; i < tamanho_chaves && atual != NULL; i++) {
        for (int j = 0; j < tamanho_valores; j++) {
            if (valores[0][j] >= atual->chave && valores[0][j] < atual->chave + 0.99) {
                inserir_ordenado_circular(&atual->lista, valores[0][j]);
            }
        }
        atual = atual->prox;
    }

    // Imprimir a lista
    imprimir_lista(lista_dupla);

    return 0;
}
