/*****************************************************************//**
 * @file    matriz_lista_ligada.c
 * @brief	
 * 
 * @author Arianna Cicero
 * @date   Março 2024
 *********************************************************************/
#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

void escreverMatrizParaArquivo(MatrizListaLigada *matriz, const char *nomearquivo) {
    FILE *arquivo = fopen(nomearquivo, "a+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo. Nao existe. ESCREVER MATRIZ PARA ARQUIVO\n");
        return;
    } else {
        printf("\n");
    }
    fprintf(arquivo,"Matriz gerada!\n");
    for (int i = 0; i < matriz->num_linhas; i++) {
        No *current = matriz->linhas[i].head;
        for (int j = 0; j < matriz->num_colunas; j++) {
            if (current != NULL) {
                fprintf(arquivo, "%d", current->data);
                if (j < matriz->num_colunas - 1 && current->next != NULL)
                    fprintf(arquivo, ";");
                current = current->next;
            } else {
                fprintf(arquivo, "0");
                if (j < matriz->num_colunas - 1)
                    fprintf(arquivo, ";");
            }
        }
        fprintf(arquivo, "\n");
    }
    fclose(arquivo);
}

void inserirElemento(MatrizListaLigada *matriz, int linha_index, int col_index, int data) {
    if (linha_index < 0 || linha_index >= matriz->num_linhas || col_index < 0 || col_index >= matriz->num_colunas) {
        printf("Indices invalidos.\n");
        return;
    }
    No *novoNo = criarNo(data);
    No *current = matriz->linhas[linha_index].head;
    if (current == NULL || col_index == 0) {
        novoNo->next = current;
        matriz->linhas[linha_index].head = novoNo;
    } else {
        for (int i = 0; i < col_index - 1; i++) {
            if (current->next == NULL) break;
            current = current->next;
        }
        novoNo->next = current->next;
        current->next = novoNo;
    }
    matriz->linhas[linha_index].comprimento++;
}

MatrizListaLigada *criarMatriz(int num_linhas, int num_colunas) {
    srand(time(NULL));

    MatrizListaLigada *matriz = (MatrizListaLigada*)malloc(sizeof(MatrizListaLigada));
    if (matriz == NULL) {
        printf("Erro ao alocar memória para a matriz.\n");
        exit(EXIT_FAILURE);
    }

    matriz->linhas = (Linha*)malloc(num_linhas * sizeof(Linha));
    if (matriz->linhas == NULL) {
        printf("Erro ao alocar memória para as linhas da matriz.\n");
        free(matriz);
        exit(EXIT_FAILURE);
    }

    matriz->num_linhas = num_linhas;
    matriz->num_colunas = num_colunas;

    for (int i = 0; i < num_linhas; i++) {
        matriz->linhas[i] = *criarLinha();
        for (int j = 0; j < num_colunas; j++) {
            int valor = rand() % 1000;
            inserirElemento(matriz, i, j, valor);
        }
    }
    return matriz;
}

void mostrarMatriz(MatrizListaLigada *matriz) {
    for (int i = 0; i < matriz->num_linhas; i++) {
        No *current = matriz->linhas[i].head;
        for (int j = 0; j < matriz->num_colunas; j++) {
            if (current != NULL && j == 0) {
                printf("%d", current->data);
                current = current->next;
            } else if (current != NULL) {
                printf("\t%d", current->data);
                current = current->next;
            } else {
                printf("\t0");
            }
        }
        printf("\n");
    }
}

int getElemento(MatrizListaLigada *matriz, int linha, int coluna) {
    if (linha < 0 || linha >= matriz->num_linhas || coluna < 0 || coluna >= matriz->num_colunas) {
        printf("Erro: Índices inválidos.\n");
        return 0;
    }

    No *current = matriz->linhas[linha].head;
    for (int i = 0; i < coluna; i++) {
        if (current == NULL) {
            printf("Erro: Não foi possível encontrar o elemento.\n");
            return 0;
        }
        current = current->next;
    }

    if (current != NULL) {
        return current->data;
    } else {
        printf("Erro: Não foi possível encontrar o elemento.\n");
        return 0;
    }
}

int calcularMaxSoma(MatrizListaLigada *matriz) {
    int maxSum = INT_MIN;
    int maxElement1 = 0;
    int maxElement2 = 0;

    for (int i = 0; i < matriz->num_linhas; i++) {
        for (int j = 0; j < matriz->num_colunas; j++) {
            int currentElement = getElemento(matriz, i, j);

            for (int k = j + 1; k < matriz->num_colunas; k++) {
                int otherElement = getElemento(matriz, i, k);
                int sum = currentElement + otherElement;
                if (sum > maxSum) {
                    maxSum = sum;

                }
            }
            for (int k = i + 1; k < matriz->num_linhas; k++) {
                int otherElement = getElemento(matriz, k, j);
                int sum = currentElement + otherElement;
                if (sum > maxSum) {
                    maxSum = sum;

                }
            }
        }
    }
    return maxSum;
}

void MostrarMaxSoma(MatrizListaLigada *matriz, const char *nomearquivo){
    FILE *arquivo = fopen(nomearquivo, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    int soma = calcularMaxSoma(matriz);
    fprintf(arquivo, "\nSoma maxima: %d\n", soma);

    fclose(arquivo);
}

void alterarElemento(MatrizListaLigada *matriz, int linha_index, int col_index, int novo_valor, const char *nomearquivo) {
    FILE *arquivo = fopen(nomearquivo, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    if (linha_index < 0 || linha_index >= matriz->num_linhas || col_index < 0 || col_index >= matriz->num_colunas) {
        fprintf(arquivo, "Índices inválidos.\n");
        fclose(arquivo);
        return;
    }

    No *current = matriz->linhas[linha_index].head;
    for (int i = 0; i < col_index; i++) {
        if (current == NULL) {
            fprintf(arquivo, "Índices inválidos.\n");
            fclose(arquivo);
            return;
        }
        current = current->next;
    }

    if (current != NULL) {
        current->data = novo_valor;
        fprintf(arquivo, "\nElemento alterado na posição [%d][%d]. Novo valor: %d\n", linha_index, col_index, novo_valor);
    } else {
        fprintf(arquivo, "Índices inválidos.\n");
    }

    fprintf(arquivo, "\nMatriz atualizada:\n");
    for (int i = 0; i < matriz->num_linhas; i++) {
        current = matriz->linhas[i].head;
        while (current != NULL) {
            fprintf(arquivo, "%d\t", current->data);
            current = current->next;
        }
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
}

void inserirLinha(MatrizListaLigada *matriz, int posicao) {
    if (posicao < 0 || posicao > matriz->num_linhas) {
        printf("Posição inválida. INSERIR LINHA\n");
        return;
    }
    matriz->linhas = realloc(matriz->linhas, (matriz->num_linhas + 1) * sizeof(Linha));
    if (matriz->linhas == NULL) {
        printf("Erro ao realocar memória para as linhas da matriz. INSERIR LINHA2\n");
        exit(EXIT_FAILURE);
    }

    for (int i = matriz->num_linhas; i > posicao; i--) {
        matriz->linhas[i] = matriz->linhas[i - 1];
    }

    matriz->linhas[posicao] = *criarLinha();
    for (int j = 0; j < matriz->num_colunas; j++) {
        int valor = rand() % 1000;  // Gera um valor aleatório entre 0 e 999
        inserirElemento(matriz, posicao, j, valor);  // Insere o valor aleatório na nova linha
    }

    matriz->num_linhas++;
}

void LinhaInserida(MatrizListaLigada *matriz, const char *nomearquivo, int posicao) {
    inserirLinha(matriz, posicao);

    FILE *arquivo = fopen(nomearquivo, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    fprintf(arquivo, "\nMatriz com linha inserida!\n");
    for (int i = 0; i < matriz->num_linhas; i++) {
        No *current = matriz->linhas[i].head;
        for (int j = 0; j < matriz->num_colunas; j++) {
            if (current != NULL) {
                fprintf(arquivo, "%d", current->data);
                if (j < matriz->num_colunas - 1 && current->next != NULL)
                    fprintf(arquivo, ";");
                current = current->next;
            } else {
                fprintf(arquivo, "0");
                if (j < matriz->num_colunas - 1)
                    fprintf(arquivo, ";");
            }
        }
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
}

void removerLinha(MatrizListaLigada *matriz, int posicao) {
    if (posicao < 0 || posicao >= matriz->num_linhas) {
        printf("Posição inválida.\n");
        return;
    }
    libertarNo(matriz->linhas[posicao].head);
    for (int i = posicao; i < matriz->num_linhas - 1; i++) {
        matriz->linhas[i] = matriz->linhas[i + 1];
    }
    matriz->linhas = realloc(matriz->linhas, (matriz->num_linhas - 1) * sizeof(Linha));
    if (matriz->linhas == NULL && matriz->num_linhas > 0) {
        printf("Erro ao realocar memória para as linhas da matriz.\n");
        exit(EXIT_FAILURE);
    }
    matriz->num_linhas--;
}

void LinhaRemovida(MatrizListaLigada *matriz, const char *nomearquivo, int posicao) {
    removerLinha(matriz, posicao);

    FILE *arquivo = fopen(nomearquivo, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    fprintf(arquivo,"\nMatriz com a linha removida!\n");
    for (int i = 0; i < matriz->num_linhas; i++) {
        No *current = matriz->linhas[i].head;
        for (int j = 0; j < matriz->num_colunas; j++) {
            if (current != NULL) {
                fprintf(arquivo, "%d", current->data);
                if (j < matriz->num_colunas - 1 && current->next != NULL)
                    fprintf(arquivo, ";");
                current = current->next;
            } else {
                // If there are no more elements in the line, print 0 or some default value
                fprintf(arquivo, "0");
                if (j < matriz->num_colunas - 1)
                    fprintf(arquivo, ";");
            }
        }
        fprintf(arquivo, "\n");
    }
    fclose(arquivo);
}

void inserirColuna(MatrizListaLigada *matriz, int posicao) {
    if (posicao < 0 || posicao > matriz->num_colunas) {
        printf("Posição inválida. INSERIR COLUNA\n");
        return;
    }
    for (int i = 0; i < matriz->num_linhas; i++) {
        int valor = rand() % 1000;
        inserirElemento(matriz, i, posicao, valor);
    }
    matriz->num_colunas++;
}

void ColunaInserida(MatrizListaLigada *matriz, const char *nomearquivo, int posicao) {
    inserirColuna(matriz, posicao);

    FILE *arquivo = fopen(nomearquivo, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    fprintf(arquivo, "\nMatriz com Coluna Inserida!\n");
    for (int i = 0; i < matriz->num_linhas; i++) {
        No *current = matriz->linhas[i].head;
        for (int j = 0; j < matriz->num_colunas; j++) {
            if (current != NULL) {
                fprintf(arquivo, "%d", current->data);
                if (j < matriz->num_colunas - 1 && current->next != NULL)
                    fprintf(arquivo, ";");
                current = current->next;
            } else {
                fprintf(arquivo, "0");
                if (j < matriz->num_colunas - 1)
                    fprintf(arquivo, ";");
            }
        }
        fprintf(arquivo, "\n");
    }
    fclose(arquivo);
}

void removerColuna(MatrizListaLigada *matriz, int posicao) {
    if (posicao < 0 || posicao >= matriz->num_colunas) {
        printf("Posição inválida. REMOVER COLUNA \n");
        return;
    }
    
    for (int i = 0; i < matriz->num_linhas; i++) {
        Linha *linha = &(matriz->linhas[i]);
        No *current = linha->head;
        No *anterior = NULL;
        int count = 0;

        while (current != NULL && count != posicao) {
            anterior = current;
            current = current->next;
            count++;
        }

        if (count == posicao) {
            if (anterior == NULL) {
                linha->head = current->next;
            } else {
                anterior->next = current->next;
            }
            free(current);
            linha->comprimento--;
        } else {
            printf("Posição inválida. REMOVER COLUNA 2\n");
        }
    }
    
    matriz->num_colunas--;
}

void ColunaRemovida(MatrizListaLigada *matriz, const char *nomearquivo, int posicao) {
    removerColuna(matriz, posicao);

    FILE *arquivo = fopen(nomearquivo, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    fprintf(arquivo, "\nMatriz com Coluna Removida!\n");
    for (int i = 0; i < matriz->num_linhas; i++) {
        No *current = matriz->linhas[i].head;
        for (int j = 0; j < matriz->num_colunas; j++) {
            if (current != NULL) {
                fprintf(arquivo, "%d", current->data);
                if (j < matriz->num_colunas - 1 && current->next != NULL)
                    fprintf(arquivo, ";");
                current = current->next;
            } else {
                fprintf(arquivo, "0");
                if (j < matriz->num_colunas - 1)
                    fprintf(arquivo, ";");
            }
        }
        fprintf(arquivo, "\n");
    }

    // Close the file
    fclose(arquivo);
}

void liberarMemoria(MatrizListaLigada *matriz) {
    for (int i = 0; i < matriz->num_linhas; i++) {
        No *current = matriz->linhas[i].head;
        while (current != NULL) {
            No *temp = current;
            current = current->next;
            free(temp); // Libera o nó atual
        }
    }
    free(matriz);
}

