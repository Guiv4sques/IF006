#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 10000

// Estrutura do nó da árvore
typedef struct No {
    int chave;
    int nivel;
    struct No *left;
    struct No *right;
    struct No *pai;
} No;

// Estrutura da árvore
typedef struct {
    No *root;
} Arvore;

// Inicializa uma nova árvore
Arvore *criarArvore() {
    Arvore *nova = malloc(sizeof(Arvore));
    nova->root = NULL;
    return nova;
}

// Insere um valor na árvore e retorna se foi inserido com sucesso
int inserirNo(Arvore *arvore, int chave) {
    No *novo = malloc(sizeof(No));
    novo->chave = chave;
    novo->left = novo->right = novo->pai = NULL;
    
    if (arvore->root == NULL) {
        arvore->root = novo;
        return 1;
    }
    
    No *aux = arvore->root;
    int altura = 0;
    
    while (1) {
        altura++;
        if (chave > aux->chave) {
            if (aux->right != NULL) {
                aux = aux->right;
            } else {
                aux->right = novo;
                novo->pai = aux;
                novo->nivel = altura;
                return 1;
            }
        } else if (chave < aux->chave) {
            if (aux->left != NULL) {
                aux = aux->left;
            } else {
                aux->left = novo;
                novo->pai = aux;
                novo->nivel = altura;
                return 1;
            }
        } else {
            return 0;
        }
    }
}

// Busca um nó com determinado valor
No *buscarNo(Arvore *arvore, int chave) {
    No *aux = arvore->root;
    while (aux != NULL) {
        if (chave > aux->chave)
            aux = aux->right;
        else if (chave < aux->chave)
            aux = aux->left;
        else
            return aux;
    }
    return NULL;
}

// Encontra o menor valor da árvore
No *buscarMinimo(Arvore *arvore) {
    No *aux = arvore->root;
    while (aux->left)
        aux = aux->left;
    return aux;
}

// Encontra o sucessor imediato de um nó
No *buscarSucessor(No *no) {
    if (no == NULL) return NULL;
    No *aux = no;
    if (aux->right != NULL) {
        aux = aux->right;
        while (aux->left)
            aux = aux->left;
        return aux;
    }
    while (aux->pai != NULL && aux == aux->pai->right) {
        aux = aux->pai;
    }
    return aux->pai;
}

// Soma os valores da subárvore de um nó
int somarSubarvore(No *no) {
    if (no == NULL) return 0;
    return no->chave + somarSubarvore(no->left) + somarSubarvore(no->right);
}

// Calcula a diferença entre as somas das subárvores leftuerda e righteita
int calcularDiferenca(No *no) {
    if (no == NULL) return 0;
    return somarSubarvore(no->right) - somarSubarvore(no->left);
}

int main() {
    system("clear||cls");
    
    FILE *entrada = fopen("L2Q2.in", "r");
    FILE *saida = fopen("L2Q2.out", "w");

    if (entrada == NULL || saida == NULL) {
        printf("Erro ao abrir arquivos!");
        return 0;
    }

    char linha[TAM];
    char *token;
    char delimitador[] = " ";
    int primeiraLinha = 1;
    
    while (fgets(linha, TAM, entrada)) {
        if (!primeiraLinha) {
            fprintf(saida, "\n");
        } else {
            primeiraLinha = 0;
        }
        
        Arvore *arvore = criarArvore();
        token = strtok(linha, delimitador);
        
        while (token) {
            inserirNo(arvore, atoi(token));
            token = strtok(NULL, delimitador);
        }
        
        No *atual = buscarMinimo(arvore);
        int primeiraImpressao = 1;
        
        while (atual != NULL) {
            if (primeiraImpressao) {
                fprintf(saida, "%d", atual->chave);
                primeiraImpressao = 0;
            } else {
                fprintf(saida, " %d", atual->chave);
            }
            
            fprintf(saida, " (%d)", calcularDiferenca(atual));
            atual = buscarSucessor(atual);
        }
    }
    
    fclose(entrada);
    fclose(saida);
    return 0;
}