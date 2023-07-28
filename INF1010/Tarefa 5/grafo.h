#ifndef GRAFO_H
#define GRAFO_H

typedef struct grafo Grafo;

// Função de criação e alocação de memória  
// para a estrutura de grafo
Grafo* criar_grafo(int num_vertices);

// Insere um vértice na estrutura de grafo valor 
// deve ser inteiro de 0 a tamanho do grafo - 1
void inserir_vertice(int chave, char valor, Grafo* grafo);

// Insere uma aresta na estrutura de grafo indo do vértice
// 'v1' para o vertice 'v2', com peso da aresta 'peso'
void inserir_aresta(int v1, int v2, int peso, Grafo* grafo);

// Libera toda a memória alocada pela estrutura de grafo
void libera_grafo(Grafo* grafo);

// Imprime os conteúdos da estrutura de grafo inteira
void imprime_grafo(Grafo* grafo);

// Calcula os menores caminhos de origem a todos os outros
// vértices usando o algoritmo de Dijkstra. A flag keep_values
// indica se os menores caminhos calculados devem ser apagados 
// ou não. Caso não o sejam, impede a reexecução para outra origem
void dijkstra_algorithm(Grafo* grafo, int origem, int keep_values);

// Realiza uma pesquisa em profundidade no grafo,
// a partir do vértice de origem
void dfs(Grafo* grafo, int origem);

#endif
