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

MatrizListaLigada *criarMatriz(int num_linhas, int num_colunas) {
    // Inicializa a semente do gerador de números aleatórios
    srand(time(NULL));

    MatrizListaLigada *matriz = (MatrizListaLigada*)malloc(sizeof(MatrizListaLigada));
    if (matriz == NULL) {
        printf("Erro ao alocar memoria para a matriz.\n");
        exit(EXIT_FAILURE);
    }
    matriz->linhas = (Linha*)malloc(num_linhas * sizeof(Linha));
    if (matriz->linhas == NULL) {
        printf("Erro ao alocar memoria para as linhas da matriz.\n");
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

void carregarMatrizDeArquivo(MatrizListaLigada *matriz, const char *documento) {
    FILE *arquivo = fopen(documento, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    int linha_index = 0;
    int col_index = 0;
    int valor;
    while (fscanf(arquivo, "%d", &valor) != EOF) {
        inserirElemento(matriz, linha_index, col_index, valor);
        col_index++;
        if (col_index == matriz->num_colunas) {
            col_index = 0;
            linha_index++;
        }
    }
    fclose(arquivo);
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

// void libertarMatriz(MatrizListaLigada *matriz) {
//     for (int i = 0; i < matriz->num_linhas; i++) {
//         No *current = matriz->linhas[i].head;
//         while (current != NULL) {
//             No *temp = current;
//             current = current->next;
//             libertarNo(temp);
//         }
//     }
//     libertarNo(matriz->linhas);
// }

int calcularMaxSoma(MatrizListaLigada *matriz) {
    // Matriz auxiliar para armazenar a soma máxima até cada posição (linha, coluna)
    int maxSum[matriz->num_linhas][matriz->num_colunas];

    // Inicializa a primeira linha e coluna da matriz auxiliar com os valores da primeira linha da matriz original
    maxSum[0][0] = matriz->linhas[0].head->data;
    for (int i = 1; i < matriz->num_colunas; i++) {
        maxSum[0][i] = maxSum[0][i - 1] + matriz->linhas[0].head->next->data;
    }
    for (int i = 1; i < matriz->num_linhas; i++) {
        maxSum[i][0] = maxSum[i - 1][0] + matriz->linhas[i].head->data;
    }

    // Calcula a soma máxima possível em cada posição da matriz auxiliar
    for (int i = 1; i < matriz->num_linhas; i++) {
        for (int j = 1; j < matriz->num_colunas; j++) {
            // Verifica a soma máxima possível considerando os valores da posição atual
            maxSum[i][j] = matriz->linhas[i].head->data + maxSum[i - 1][j];
            if (maxSum[i][j - 1] > maxSum[i][j]) {
                maxSum[i][j] = maxSum[i][j - 1];
            }
        }
    }

    // A última posição da matriz auxiliar contém a soma máxima possível
    return maxSum[matriz->num_linhas - 1][matriz->num_colunas - 1];
}

void alterarElemento(MatrizListaLigada *matriz, int linha_index, int col_index, int novo_valor) {
    if (linha_index < 0 || linha_index >= matriz->num_linhas || col_index < 0 || col_index >= matriz->num_colunas) {
        printf("Índices inválidos.\n");
        return;
    }
    No *current = matriz->linhas[linha_index].head;
    for (int i = 0; i < col_index; i++) {
        if (current == NULL) {
            printf("Índices inválidos.\n");
            return;
        }
        current = current->next;
    }
    if (current != NULL) {
        current->data = novo_valor;
    }
}

void inserirLinha(MatrizListaLigada *matriz, int posicao) {
    if (posicao < 0 || posicao > matriz->num_linhas) {
        printf("Posição inválida.\n");
        return;
    }
    Linha *novaLinha = criarLinha();
    matriz->linhas = realloc(matriz->linhas, (matriz->num_linhas + 1) * sizeof(Linha));
    if (matriz->linhas == NULL) {
        printf("Erro ao realocar memória para as linhas da matriz.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = matriz->num_linhas; i > posicao; i--) {
        matriz->linhas[i] = matriz->linhas[i - 1];
    }
    matriz->linhas[posicao] = *novaLinha;
    matriz->num_linhas++;
}

void inserirColuna(MatrizListaLigada *matriz, int posicao) {
    if (posicao < 0 || posicao > matriz->num_colunas) {
        printf("Posição inválida.\n");
        return;
    }
    for (int i = 0; i < matriz->num_linhas; i++) {
        inserirElemento(matriz, i, posicao, 0); // Insere zeros em todas as posições da nova coluna
    }
    matriz->num_colunas++;
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


void removerColuna(MatrizListaLigada *matriz, int posicao) {
    if (posicao < 0 || posicao >= matriz->num_colunas) {
        printf("Posição inválida.\n");
        return;
    }
    
    for (int i = 0; i < matriz->num_linhas; i++) {
        Linha *linha = &(matriz->linhas[i]);
        No *current = linha->head;
        No *anterior = NULL;
        int count = 0;

        while (current != NULL && count != posicao) {
            anterior = current;
            current = current->next; // Corrigido para 'next'
            count++;
        }

        if (count == posicao) {
            if (anterior == NULL) { // Se for o primeiro elemento
                linha->head = current->next; // Corrigido para 'next'
            } else {
                anterior->next = current->next; // Corrigido para 'next'
            }
            free(current);
            linha->comprimento--; // Corrigido para 'comprimento'
        } else {
            printf("Posição inválida.\n");
        }
    }
    
    matriz->num_colunas--;
}



