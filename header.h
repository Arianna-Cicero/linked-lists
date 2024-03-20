/*****************************************************************//**
 * @file    header.h
 * @brief   Biblioteca para manipulação de uma matriz representada por listas ligadas
 * 
 * @author  Arianna Cicero
 * @date    Março 2024
 *********************************************************************/

#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>

// Estrutura de nó
typedef struct No {
    int data;
    struct No *next;
} No;

// Estrutura de linha
typedef struct Linha {
    No *head;
    int comprimento;
} Linha;

// Estrutura de matriz
typedef struct MatrizListaLigada {
    Linha *linhas;
    int num_linhas;
    int num_colunas;
} MatrizListaLigada;

// Funções para manipulação de nós
No *criarNo(int data);
void libertarNo(No *no);

// Funções para manipulação de linhas
Linha *criarLinha();

// Funções para manipulação de matriz
MatrizListaLigada *criarMatriz(int num_linhas, int num_colunas);
void inserirElemento(MatrizListaLigada *matriz, int linha_index, int col_index, int data);
void escreverMatrizParaArquivo(MatrizListaLigada *matriz, const char *nomearquivo);
void mostrarMatriz(MatrizListaLigada *matriz);
void LinhaRemovida(MatrizListaLigada *matriz, const char *nomearquivo, int posicao);
void ColunaRemovida(MatrizListaLigada *matriz, const char *nomearquivo, int posicao);
void LinhaInserida(MatrizListaLigada *matriz, const char *nomearquivo, int posicao);

/*
void libertarMatriz(MatrizListaLigada *matriz);
int calcularMaxSoma(MatrizListaLigada *matriz);
void removerColuna(MatrizListaLigada *matriz, int posicao);
void removerLinha(MatrizListaLigada *matriz, int posicao);
void alterarElemento(MatrizListaLigada *matriz, int linha_index, int col_index, int novo_valor);*/

#endif 
