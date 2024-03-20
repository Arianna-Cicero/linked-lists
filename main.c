/*****************************************************************//**
 * @file    main.c
 * @brief
 *
 * @author Arianna Cicero
 * @date   Março 2024
 *********************************************************************/
#include "header.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int num_linhas = 5, num_colunas = 5;
    char direcao[]= "/home/arianna/CLionProjects/linked-lists/matriz.txt";

    MatrizListaLigada *matriz = criarMatriz(num_linhas, num_colunas);

    escreverMatrizParaArquivo(matriz, direcao);

    LinhaRemovida(matriz, direcao, 3);

    ColunaRemovida(matriz, direcao, 1);

    LinhaInserida(matriz, direcao, 5);

    return 0;
}

