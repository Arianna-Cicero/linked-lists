/*****************************************************************//**
 * @file    linha_lista_ligada.c
 * @brief	
 * 
 * @author Arianna Cicero
 * @date   Março 2024
 *********************************************************************/
#include "header.h"
#include <stdlib.h>
#include <stdio.h>

Linha *criarLinha() {
    Linha *linha = (Linha*)malloc(sizeof(Linha));
    if (linha == NULL) {
        printf("Erro ao alocar memória para a linha.\n");
        exit(EXIT_FAILURE);
    }
    linha->head = NULL;
    linha->comprimento = 0;
    return linha;
}
