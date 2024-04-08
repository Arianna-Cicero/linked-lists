/*****************************************************************//**
 * @file    main.c
 * @brief
 *
 * @author Arianna Cicero
 * @date   Março 2024
 *********************************************************************/
#include "header.h"
#include <stdio.h>

int main() {
    int num_linhas = 5, num_colunas = 5;
    int linha=3,coluna=3;
    char direcao[]= "/home/arianna/CLionProjects/linked-lists/matriz.txt";

    MatrizListaLigada *matriz = criarMatriz(num_linhas, num_colunas);

    printf("Matriz gerada!\n");
    mostrarMatriz(matriz);

    escreverMatrizParaArquivo(matriz, direcao);

    LinhaRemovida(matriz, direcao, 3);

    ColunaRemovida(matriz, direcao, 1);

    LinhaInserida(matriz, direcao, 1);

    ColunaInserida(matriz, direcao, 3);

    alterarElemento(matriz, linha, coluna, 0, direcao);

    MostrarMaxSoma(matriz, direcao);

    liberarMemoria(matriz);
    return 0;
}

