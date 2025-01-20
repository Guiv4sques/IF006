//Dupla: Guilherme Cauê Andrade Vasques (20241160036), Papai do Céu;
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Estrutura para armazenar listas
typedef struct {
    int *elementos;
    int tamanho;
    int soma;
} Lista;

// Função para comparar números inteiros (para qsort)
int comparar_inteiros(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Função para comparar listas pela soma dos elementos
int comparar_listas(const void *a, const void *b) {
    Lista *listaA = (Lista*)a;
    Lista *listaB = (Lista*)b;
    return listaA->soma - listaB->soma;
}

int main() {
    // Exemplo
    const char *entrada = "start 3 -1 2 0 start 4 2 5 1 0 start 2 1 -3 start 2 1 100 -3 start 2 101 -3 start 6 -8 15 0 start 5 -1 3 2 start 5 -1 30 2 start 5 -1 32 2 start 5 -1 35 2 start 3 -1 2 0 start 4 2 5 1 0 start 2 1 -3 start 2 1 100 -3 start 2 101 -3 start 6 -8 15 0 start 5 -1 3 2 start 5 -1 30 2 start 5 -1 32 2 start 5 -1 35 2 start 3 -1 2 0 start 4 2 5 1 0 start 2 1 -3 start 2 1 100 -3 start 2 101 -3";
    Lista listas[100];
    int num_listas = 0;

    // Variáveis auxiliares
    int numeros[100];
    int tamanho_atual = 0;
    int soma_atual = 0;

    for (const char *ptr = entrada; *ptr; ptr++) {
        if (*ptr == 's' && *(ptr + 1) == 't') {
            // Salvar a lista anterior, se existir
            if (tamanho_atual > 0) {
                listas[num_listas].elementos = malloc(tamanho_atual * sizeof(int));
                for (int i = 0; i < tamanho_atual; i++) {
                    listas[num_listas].elementos[i] = numeros[i];
                }
                listas[num_listas].tamanho = tamanho_atual;
                listas[num_listas].soma = soma_atual;
                num_listas++;
            }

            // Reiniciar variáveis para a próxima lista
            tamanho_atual = 0;
            soma_atual = 0;

            // Pular "start"
            ptr += 4;
        } else if (*ptr >= '0' && *ptr <= '9' || *ptr == '-') {
            // Ler número
            int numero;
            sscanf(ptr, "%d", &numero);
            numeros[tamanho_atual++] = numero;
            soma_atual += numero;

            // Avançar o ponteiro até o final do número
            while (*ptr >= '0' && *ptr <= '9' || *ptr == '-') ptr++;
        }
    }

    // Salvar a última lista
    if (tamanho_atual > 0) {
        listas[num_listas].elementos = malloc(tamanho_atual * sizeof(int));
        for (int i = 0; i < tamanho_atual; i++) {
            listas[num_listas].elementos[i] = numeros[i];
        }
        listas[num_listas].tamanho = tamanho_atual;
        listas[num_listas].soma = soma_atual;
        num_listas++;
    }

    // Ordenar cada lista individualmente
    for (int i = 0; i < num_listas; i++) {
        qsort(listas[i].elementos, listas[i].tamanho, sizeof(int), comparar_inteiros);
    }

    // Ordenar as listas pela soma dos elementos
    qsort(listas, num_listas, sizeof(Lista), comparar_listas);

    // Imprimir as listas ordenadas
    for (int i = 0; i < num_listas; i++) {
        printf("start ");
        for (int j = 0; j < listas[i].tamanho; j++) {
            printf("%d ", listas[i].elementos[j]);
        }
        printf("\n");
        free(listas[i].elementos); // Liberar memória
    }

    return 0;
}
