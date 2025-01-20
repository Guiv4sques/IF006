//Dupla: Guilherme Cau� Andrade Vasques (20241160036), Papai do C�u;
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_ELEMENTOS 100
#define MAX_NOME 50

// Estrutura para a pilha de texto
typedef struct {
    char elementos[MAX_ELEMENTOS][MAX_NOME];
    int topo;
} Pilha;

// Fun��o para inicializar a pilha
void inicializar_pilha(Pilha *p) {
    p->topo = -1;
}

// Fun��o para verificar se a pilha est� vazia
int pilha_vazia(Pilha *p) {
    return p->topo == -1;
}

// Fun��o para verificar se a pilha est� cheia
int pilha_cheia(Pilha *p) {
    return p->topo == MAX_ELEMENTOS - 1;
}

// Fun��o para empilhar um elemento
void push(Pilha *p, const char *nome) {
    if (!pilha_cheia(p)) {
        strcpy(p->elementos[++p->topo], nome);
    }
}

// Fun��o para desempilhar um elemento
void pop(Pilha *p, char *nome) {
    if (!pilha_vazia(p)) {
        strcpy(nome, p->elementos[p->topo--]);
    }
}

// Fun��o para ordenar alfabeticamente a pilha temporariamente
void ordenar_pilha(Pilha *p) {
    for (int i = 0; i <= p->topo; i++) {
        for (int j = i + 1; j <= p->topo; j++) {
            if (strcmp(p->elementos[i], p->elementos[j]) > 0) {
                char temp[MAX_NOME];
                strcpy(temp, p->elementos[i]);
                strcpy(p->elementos[i], p->elementos[j]);
                strcpy(p->elementos[j], temp);
            }
        }
    }
}

// Fun��o para gerenciar a pilha mantendo a ordena��o
void empilhar_ordenado(Pilha *p, const char *novo_nome) {
    Pilha auxiliar;
    inicializar_pilha(&auxiliar);

    char temp[MAX_NOME];

    // Desempilhar elementos at� encontrar a posi��o correta
    while (!pilha_vazia(p) && strcmp(p->elementos[p->topo], novo_nome) > 0) {
        pop(p, temp);
        push(&auxiliar, temp);
        printf("pop\n");
    }

    // Empilhar o novo elemento
    push(p, novo_nome);
    printf("push-%s\n", novo_nome);

    // Reempilhar os elementos da pilha auxiliar
    while (!pilha_vazia(&auxiliar)) {
        pop(&auxiliar, temp);
        push(p, temp);
        printf("push-%s\n", temp);
    }
}

int main() {
    Pilha pilha;
    inicializar_pilha(&pilha);

    // Entrada
    const char *entrada[] = {"Bruno", "Dani", "Carla", "Ant�nia", "Walter", "Maria", "Jo�o", "Maria", "Jo�o", "Opa", "Bula", "Chica", "Suca", "Mara", "Nara", "Cabanca"};
    int tamanho_entrada = sizeof(entrada) / sizeof(entrada[0]);

    for (int i = 0; i < tamanho_entrada; i++) {
        empilhar_ordenado(&pilha, entrada[i]);
    }

    // Exibir o estado final da pilha
    printf("\nEstado final da pilha:\n");
    for (int i = 0; i <= pilha.topo; i++) {
        printf("%s\n", pilha.elementos[i]);
    }

    return 0;
}
