/*****************************************************************//**
 * @file    no_lista_ligada.c
 * @brief	
 * 
 * @author Arianna Cicero
 * @date   Março 2024
 *********************************************************************/
#include "header.h"
#include <stdlib.h>
#include <stdio.h>

No *criarNo(int data) {
    No *novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro ao alocar memória para o novo nó. CRIAR NO\n");
        exit(EXIT_FAILURE);
    }
    novoNo->data = data;
    novoNo->next = NULL;
    return novoNo;
}

void libertarNo(No* no) {
    // Verifica se o nó não é nulo
    if (no != NULL) {
        // Libera a memória alocada para o nó
        free(no);
    }
}