// APS: Desenvolvimento de Sistema para Análise de Performance de Algoritmos de Ordenação de Dados

// ALUNO 1: Matheus Henrique dos Santos Silva, N8522F6
// ALUNO 2: Philipe Gabriel Dos Santos Simeão, N277DF2
// ALUNO 3: Gabriel Melero Thomaz, G806620


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


//Função para gerar um arquivo de numeros aleatórios
void gerar_numeros_aleatorios(int quantidade) {
    static int contador = 0; 
    contador++;

    char nome_arquivo[50];
    sprintf(nome_arquivo, "numeros_gerados_%d.txt", contador);

    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    srand(time(NULL) + contador); 
    for (int i = 0; i < quantidade; i++) {
        int numero = (rand() % 10000);
        fprintf(arquivo, "%d\n", numero);
    }

    fclose(arquivo);

    printf("Arquivo %s criado com %d numeros aleatorios.\n", nome_arquivo, quantidade);
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
        printf("Nenhum numero encontrado no arquivo ou erro de leitura.\n");
        return NULL;
    }

    FILE *arquivo = fopen(caminho_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    int *array = (int *)malloc(*quantidade * sizeof(int));
    if (array == NULL) {
        printf("Erro ao alocar memoria.\n");
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
        printf("Erro ao ler os numeros do arquivo.\n");
        return;
    }

    printf("Numeros no arquivo %s:\n", caminho_arquivo);
    for (int i = 0; i < quantidade; i++) {
        printf("%d\n", numeros[i]);
    }

    free(numeros);
}

// Função Bubble Sort
void bubbleSort(int array[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int aux = array[j];
                array[j] = array[j + 1];
                array[j + 1] = aux;
            }
        }
    }
}

// Função Insertion Sort
void insertionSort(int array[], int n) {
    for (int i = 1; i < n; i++) {
        int chave = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > chave) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = chave;
    }
}

// Função Selection Sort
void selectionSort(int array[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
        }

        int aux = array[minIndex];
        array[minIndex] = array[i];
        array[i] = aux;
    }
}

// Função para salvar o array ordenado no arquivo
void salvar_numeros_arquivo(const char *caminho_arquivo, int array[], int quantidade) {
    FILE *arquivo = fopen(caminho_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        fprintf(arquivo, "%d\n", array[i]);
    }

    fclose(arquivo);
    printf("Numeros ordenados salvos no arquivo %s.\n", caminho_arquivo);
}

void linha(){
	printf("\n----------------------------------\n");
}


int main() {
    int opcao, quantidade, metodo;
    char caminho_arquivo[100];
    int *numeros = NULL;
    clock_t inicio, fim;
    double tempo_gasto;

    while (1) {
    	
        printf("\nMenu:\n");
        printf("1. Gerar numeros aleatorios e salvar em um arquivo\n");
        printf("2. Carregar e ordenar numeros de um arquivo\n");
        printf("3. Mostrar numeros do arquivo\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
		linha();
        switch (opcao) {
            case 1:
                printf("Digite a quantidade de numeros aleatorios para gerar: ");
                scanf("%d", &quantidade);
                gerar_numeros_aleatorios(quantidade);
                break;

            case 2:
            	linha();
                printf("Digite o caminho e nome do arquivo: ");
                scanf("%s", caminho_arquivo);
                numeros = ler_numeros_arquivo(caminho_arquivo, &quantidade);

                if (numeros == NULL) {
                    printf("Erro ao carregar os numeros do arquivo.\n");
                    break;
                }
                
                linha();

                printf("Escolha o metodo de ordenacao:\n");
                printf("1. Bubble Sort\n");
                printf("2. Insertion Sort\n");
                printf("3. Selection Sort\n");
                printf("Escolha uma opção: ");
                scanf("%d", &metodo);

                inicio = clock();  // Início do cronômetro
                linha();

                switch (metodo) {
                    case 1:
                        bubbleSort(numeros, quantidade);
                        printf("Numeros ordenados com Bubble Sort.\n");
                        break;
                    case 2:
                        insertionSort(numeros, quantidade);
                        printf("Numeros ordenados com Insertion Sort.\n");
                        break;
                    case 3:
                        selectionSort(numeros, quantidade);
                        printf("Numeros ordenados com Selection Sort.\n");
                        break;
                    default:
                        printf("Opcao invalida de metodo de ordenacao.\n");
                        free(numeros);
                        continue;
                }

                fim = clock();  // Fim do cronômetro
                tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;  // Tempo em segundos

                printf("Tempo gasto para ordenacao: %f segundos\n", tempo_gasto);
                

                salvar_numeros_arquivo(caminho_arquivo, numeros, quantidade);
                
                free(numeros);
                break;

            case 3:
            	linha();
                printf("Digite o caminho e nome do arquivo: ");
                scanf("%s", caminho_arquivo);
                mostrar_numeros_arquivo(caminho_arquivo);
                break;

            case 4:
            	
                printf("Saindo do programa.\n");
                return 0;

            default:
            	linha();
                printf("Opcao invalida! Tente novamente.\n");
        
        }
        linha();
    }
    
}
