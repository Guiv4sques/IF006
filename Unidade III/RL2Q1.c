#include <stdlib.h>
#include <stdio.h>

// Estrutura para o nó da árvore binária
typedef struct Node {
    int key;
    int height;
    struct Node *left, *right;
} Node;

// Função para criar um novo nó
Node* createNode(int key, int height) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->height = height;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Função para inserir um nó na árvore binária
Node* insert(Node* root, int key, int height, int* max, int* pred) {
    if (root == NULL) {
        if (key > *max) {
            *max = key;
        }
        return createNode(key, height);
    }

    if (key < root->key) {
        *pred = root->key;
        root->left = insert(root->left, key, height + 1, max, pred);
    } else {
        root->right = insert(root->right, key, height + 1, max, pred);
    }

    return root;
}

// Função para encontrar o predecessor de um nó
int findPredecessor(Node* root, int key) {
    Node* current = root;
    int pred = -1;

    while (current != NULL) {
        if (key <= current->key) {
            current = current->left;
        } else {
            pred = current->key;
            current = current->right;
        }
    }

    return pred;
}

// Função para imprimir a altura dos nós na ordem de inserção
void printInsertionHeights(Node* root) {
    if (root == NULL) return;

    printInsertionHeights(root->left);
    printf("%d ", root->height);
    printInsertionHeights(root->right);
}

// Função principal
int main() {
    FILE *file = fopen("L2Q1.in", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    Node* root = NULL;
    int key, max = -1;

    printf("Alturas dos nós na ordem de inserção:\n");
    while (fscanf(file, "%d", &key) != EOF) {
        int pred = -1;
        root = insert(root, key, 0, &max, &pred);
        printf("%d ", 0);
    }
    printf("\n\n");

    fclose(file);

    printf("Valor máximo: %d\n", max);
    int pred = findPredecessor(root, max);
    if (pred == -1) {
        printf("Predecessor: NaN\n");
    } else {
        printf("Predecessor: %d\n", pred);
    }

    return 0;
}
