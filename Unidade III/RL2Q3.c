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

// Função para inserir ou "remover" (se não existir, vira inserção)
Node* insertOrRemove(Node* root, char operation, int key, int height) {
    if (operation == 'a') {
        if (root == NULL) {
            return createNode(key, height);
        }

        if (key < root->key) {
            root->left = insertOrRemove(root->left, 'a', key, height + 1);
        } else if (key > root->key) {
            root->right = insertOrRemove(root->right, 'a', key, height + 1);
        }
        return root;
    } else if (operation == 'r') {
        Node* temp;
        if (root == NULL) {
            return createNode(key, height); // Inserção no caso de remoção inválida
        }

        if (key < root->key) {
            root->left = insertOrRemove(root->left, 'r', key, height + 1);
        } else if (key > root->key) {
            root->right = insertOrRemove(root->right, 'r', key, height + 1);
        } else {
            if (root->left == NULL) {
                temp = root->right;
                free(root);
                return temp;
            } else if (root->right == NULL) {
                temp = root->left;
                free(root);
                return temp;
            }

            temp = root->right;
            while (temp && temp->left != NULL) {
                temp = temp->left;
            }

            root->key = temp->key;
            root->right = insertOrRemove(root->right, 'r', temp->key, height + 1);
        }
    }
    return root;
}

// Função para imprimir os nós e suas alturas
void printTree(Node* root) {
    if (root == NULL) return;

    printTree(root->left);
    printf("%d (%d) ", root->key, root->height);
    printTree(root->right);
}

// Função principal
int main() {
    FILE *file = fopen("L2Q3.in", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    Node* root = NULL;
    char operation;
    int key;

    while (fscanf(file, " %c %d", &operation, &key) != EOF) {
        root = insertOrRemove(root, operation, key, 0);
    }

    fclose(file);

    printf("Árvore final (nó e altura):\n");
    printTree(root);
    printf("\n");

    return 0;
}
