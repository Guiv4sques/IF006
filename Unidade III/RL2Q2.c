#include <stdlib.h>
#include <stdio.h>

// Estrutura para o nó da árvore binária
typedef struct Node {
    int key;
    int leftSum;
    int rightSum;
    struct Node *left, *right;
} Node;

// Função para criar um novo nó
Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->leftSum = 0;
    newNode->rightSum = 0;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Função para inserir um nó na árvore binária sem duplicados
Node* insert(Node* root, int key) {
    if (root == NULL) {
        return createNode(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
        root->leftSum += key;
    } else if (key > root->key) {
        root->right = insert(root->right, key);
        root->rightSum += key;
    }

    return root;
}

// Função para calcular e imprimir as diferenças
void printDifferences(Node* root) {
    if (root == NULL) return;

    printDifferences(root->left);
    printf("%d (%d) ", root->key, root->rightSum - root->leftSum);
    printDifferences(root->right);
}

// Função principal
int main() {
    FILE *file = fopen("L2Q2.in", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    Node* root = NULL;
    int key;

    while (fscanf(file, "%d", &key) != EOF) {
        root = insert(root, key);
    }

    fclose(file);

    printf("Diferenças (soma direita - soma esquerda):\n");
    printDifferences(root);
    printf("\n");

    return 0;
}
