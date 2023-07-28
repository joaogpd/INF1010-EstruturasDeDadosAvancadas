// Nota 10 de 10

#include <stdio.h>
#include "grafo.h"

#define MAX_VERTICES 7

int main(void) {
    // Cria grafo
    Grafo* grafo = criar_grafo(MAX_VERTICES);

    // Insere os vértices
    inserir_vertice(0, 'A', grafo);
    inserir_vertice(1, 'B', grafo);
    inserir_vertice(2, 'C', grafo);
    inserir_vertice(3, 'D', grafo);
    inserir_vertice(4, 'E', grafo);
    inserir_vertice(5, 'F', grafo);
    inserir_vertice(6, 'H', grafo);

    // Insere as arestas
    inserir_aresta(0, 1, 5, grafo);
    inserir_aresta(0, 2, 4, grafo);
    inserir_aresta(0, 3, 2, grafo);
    inserir_aresta(1, 2, 6, grafo);
    inserir_aresta(1, 4, 6, grafo);
    inserir_aresta(1, 6, 9, grafo);
    inserir_aresta(2, 3, 3, grafo);
    inserir_aresta(2, 4, 4, grafo);
    inserir_aresta(3, 4, 5, grafo);
    inserir_aresta(3, 5, 9, grafo);
    inserir_aresta(4, 6, 6, grafo);
    inserir_aresta(4, 5, 2, grafo);
    inserir_aresta(5, 6, 3, grafo);

    // Imprime os contéudos do grafo
    imprime_grafo(grafo);

    // Realiza percurso dfs do grafo
    // com o vértice A de origem
    printf("DFS: Origem A\n");
    dfs(grafo, 0);
    
    // Executa o algoritmo de Dijkstra
    // com o vértice A como origem
    printf("Dijkstra: Origem A\n");
    dijkstra_algorithm(grafo, 0, 0);

    // Libera memória do grafo
    libera_grafo(grafo);

    return 0;
}