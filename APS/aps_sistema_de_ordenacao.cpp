// APS: Desenvolvimento de Sistema para Análise de Performance de Algoritmos de Ordenação de Dados

// ALUNO 1: Matheus Henrique dos Santos Silva, N8522F6
// ALUNO 2: Philipe Gabriel Dos Santos Simeão, N277DF2
// ALUNO 3: Gabriel Melero Thomaz, G806620

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//Função para gerar um arquivo de numeros aleatórios
void gerar_numeros_aleatorios(int quantidade) {
    static int contador = 0; 
    contador++;

    char nome_arquivo[50];
    sprintf(nome_arquivo, "arq_extensao_gerada_%d.txt", contador);

    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    srand(time(NULL) + contador); 
    for (int i = 0; i < quantidade; i++) {
        int numero = (rand() % 10000) + 100000;
        fprintf(arquivo, "%d\n", numero);
    }

    fclose(arquivo);

    printf("Arquivo %s criado com %d números aleatórios.\n", nome_arquivo, quantidade);
}

// Função para contar quantos números inteiros estão no arquivo
int contar_numeros_arquivo(const char *caminho_arquivo) {
    FILE *arquivo = fopen(caminho_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return -1;
    }

    int contador = 0;
    int numero;
    while (fscanf(arquivo, "%d", &numero) == 1) {
        contador++;
    }

    fclose(arquivo);
    return contador;
}

// Função para ler os números do arquivo e armazená-los em um array
int* ler_numeros_arquivo(const char *caminho_arquivo, int *quantidade) {
    *quantidade = contar_numeros_arquivo(caminho_arquivo);
    if (*quantidade <= 0) {
        printf("Nenhum número encontrado no arquivo ou erro de leitura.\n");
        return NULL;
    }

    FILE *arquivo = fopen(caminho_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    int *array = (int *)malloc(*quantidade * sizeof(int));
    if (array == NULL) {
        printf("Erro ao alocar memória.\n");
        fclose(arquivo);
        return NULL;
    }

    for (int i = 0; i < *quantidade; i++) {
        fscanf(arquivo, "%d", &array[i]);
    }

    fclose(arquivo);
    return array;
}

// Função para mostrar os números do arquivo
void mostrar_numeros_arquivo(const char *caminho_arquivo) {
    int quantidade;
    int *numeros = ler_numeros_arquivo(caminho_arquivo, &quantidade);

    if (numeros == NULL) {
        printf("Erro ao ler os números do arquivo.\n");
        return;
    }

    printf("Números no arquivo %s:\n", caminho_arquivo);
    for (int i = 0; i < quantidade; i++) {
        printf("%d\n", numeros[i]);
    }

    free(numeros);
}


int main() {

}



