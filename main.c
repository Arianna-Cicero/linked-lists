/*****************************************************************//**
 * @file    main.c
 * @brief	
 * 
 * @author Arianna Cicero
 * @date   Março 2024
 *********************************************************************/
#include "matriz_lista_ligada.c"
#include <stdio.h>
#include <stdlib.h>

int main() {
    
    // Definição de uma estrutura de dados dinâmica ED
    int num_linhas = 5, num_colunas = 5;
    MatrizListaLigada *matriz = criarMatriz(num_linhas, num_colunas);       
          
    // Carregamento para a estrutura de dados da alínea anterior ED 
    carregarMatrizDeArquivo(matriz, "matriz.txt");
    
    // 3. Alteração dos inteiros constantes em ED
    alterarElemento(matriz, 0, 0, 100); // Altera o elemento na posição (0, 0) para 100
    
    // 4. Inserção de novas linhas/colunas na matriz representada por ED
    inserirLinha(matriz, 2); // Insere uma nova linha na posição 2
    inserirColuna(matriz, 3); // Insere uma nova coluna na posição 3
    
    // 5. Remoção de linhas/colunas na matriz representada por ED
    removerLinha(matriz, 1); // Remove a linha na posição 1
    removerColuna(matriz, 2); // Remove a coluna na posição 2
    
    // 6. Listagem de forma tabular na consola de todos os inteiros constantes na estrutura de dados ED
    printf("Matriz após operações:\n");
    mostrarMatriz(matriz);
    
    // 7. Cálculo da soma máxima possível dos inteiros em ED   
    // Calcula a soma máxima possível dos inteiros na matriz
    int maxSoma = calcularMaxSoma(matriz);
    printf("Soma máxima possível: %d\n", maxSoma);

    // Libera a memória alocada para a matriz
    // libertarMatriz(matriz);
                
    return 0;
}
