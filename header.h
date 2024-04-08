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

typedef struct No {
    int data;
    struct No *next;
} No;

typedef struct Linha {
    No *head;
    int comprimento;
} Linha;

typedef struct MatrizListaLigada {
    Linha *linhas;
    int num_linhas;
    int num_colunas;
} MatrizListaLigada;

No *criarNo(int data);
void libertarNo(No *no);

Linha *criarLinha();

MatrizListaLigada *criarMatriz(int num_linhas, int num_colunas);
void escreverMatrizParaArquivo(MatrizListaLigada *matriz, const char *nomearquivo);
void mostrarMatriz(MatrizListaLigada *matriz);
void LinhaRemovida(MatrizListaLigada *matriz, const char *nomearquivo, int posicao);
void ColunaRemovida(MatrizListaLigada *matriz, const char *nomearquivo, int posicao);
void LinhaInserida(MatrizListaLigada *matriz, const char *nomearquivo, int posicao);
void ColunaInserida(MatrizListaLigada *matriz, const char *nomearquivo, int posicao);
void MostrarMaxSoma(MatrizListaLigada *matriz, const char *nomearquivo);
void alterarElemento(MatrizListaLigada *matriz, int linha_index, int col_index, int novo_valor, const char *nomearquivo);
void liberarMemoria(MatrizListaLigada *matriz);
/*
void libertarMatriz(MatrizListaLigada *matriz);
void alterarElemento(MatrizListaLigada *matriz, int linha_index, int col_index, int novo_valor);*/

#endif 
