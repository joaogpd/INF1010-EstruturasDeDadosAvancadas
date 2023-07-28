#include <stdlib.h>
#include <stdio.h>

typedef struct grafo Grafo;
typedef struct vertice Vertice;
typedef struct aresta Aresta;
typedef struct pilha Pilha;
typedef struct fila Fila;
typedef int(*comp_func)(Aresta*, Aresta*);

// Estrutura de grafo, com lista de adjacências
struct grafo {
    Vertice** vertices;
    int ocupados;
    int num_vertices;
};

// Estrutura de vértice de grafo, também
// usada como nó de fila e de pilha
struct vertice {
    int chave;
    char valor;
    int num_arestas;
    Aresta* arestas;
    int menor_caminho;
    Vertice* downprox;
};

// Estrutura de aresta de grafo
struct aresta {
    int vertice2;
    int peso;
    Aresta* prox;
};


// Estrutura de cabeça de pilha
struct pilha {
    Vertice* topo;
};

// Estrutura de cabeça de fila
struct fila {
    Vertice* inicio;
    Vertice* fim;
};

// Funções de vértice

// Função de criação e alocação de memória  
// para uma estrutura de vértice, de chave e valor
Vertice* criar_vertice(int chave, char valor) {
    Vertice* novo_vertice = (Vertice*)malloc(sizeof(Vertice));
    if (novo_vertice == NULL) {
        fprintf(stderr, "ERRO: falha de alocação de memória em criar_vertice\n");
        exit(-1);
    }
    novo_vertice->chave = chave;
    novo_vertice->valor = valor;
    novo_vertice->num_arestas = 0;
    novo_vertice->arestas = NULL;
    // -1 correspondente a infinito, para o algoritmo de Dijkstra
    novo_vertice->menor_caminho = -1;
    novo_vertice->downprox = NULL;
    return novo_vertice;
}

// Realiza a impressão de parte dos conteúdos de uma estrutura vértice
// Utilizada para debugging e testagem
void print_vertice(Vertice* vertice) {
    printf("Chave: %d, Valor: %c\n", vertice->chave, vertice->valor);
    printf("downprox: %p, Self: %p\n", vertice->downprox, vertice);
}

// Funções de aresta

// Função de criar e alocar espaço para
// uma estrutura de aresta de grafo
Aresta* criar_aresta(int v2, int peso) {
    Aresta* nova_aresta = (Aresta*)malloc(sizeof(Aresta));
    if (nova_aresta == NULL) {
        fprintf(stderr, "ERRO: falha de alocação de memória em criar_aresta\n");
        exit(-1);
    }
    nova_aresta->vertice2 = v2;
    nova_aresta->peso = peso;
    nova_aresta->prox = NULL;
    return nova_aresta;
}

// retorna 1 se o valor de vertice2 de aresta é maior
// que o valor de vertice2 de cursor
int compara_vertice(Aresta* aresta, Aresta* cursor) {
    return (aresta->vertice2 > cursor->vertice2);
}

// retorna 1 se o valor de peso de aresta é menor
// que o valor de peso de cursor
int compara_peso(Aresta* aresta, Aresta* cursor) {
    return (aresta->peso < cursor->peso);
}


// Função de inserção em lista encadeada de Aresta de forma
// a manter a ordenação, para lista de adjacências de grafo
// Se char peso_ou_vertice = 1, compara vertice
// Se char peso_ou_vertice = 0, compara peso
Aresta* inserir_ordenado_aresta(Aresta* aresta, Aresta* head, char peso_ou_vertice) {
    if (head == NULL) {
        fprintf(stderr, "ERRO: cabeça de aresta com valor NULL em inserir_ordenado_aresta\n");
        return NULL;
    } 
    // ponteiro para função de comparação
    comp_func primeiro_menor;
    if (peso_ou_vertice)
        primeiro_menor = compara_vertice;
    else 
        primeiro_menor = compara_peso;
    // cursores inicializados
    Aresta* prev = NULL;
    Aresta* cursor = head;
    while (cursor != NULL) {
        // se o valor inserido for menor que o atual, insere
        if (primeiro_menor(aresta, cursor)) {
            // caso de valor inserido na primeira posição, aresta vira head
            if (prev == NULL) {
                aresta->prox = head;
                return aresta;
            } else {
                prev->prox = aresta;
                aresta->prox = cursor;
                return head;
            }
        }
        prev = cursor;
        cursor = cursor->prox;
    }

    // caso de valor inserido na última posição
    if (cursor == NULL) {
        prev->prox = aresta;
    }

    return head;
}

// Funções de pilha

// Insere um vértice no topo de uma estrutura de pilha
void push_vertice(Pilha* pilha, Vertice* vertice) {
    // caso de pilha vazia
    if (pilha->topo == NULL) {
        pilha->topo = vertice;
        vertice->downprox = NULL;
    } else {
        vertice->downprox = pilha->topo;
        pilha->topo = vertice;
    }
}

// Retira um vértice do topo de uma estrutura de pilha
Vertice* pop_vertice(Pilha* pilha) {
    // verifica se pilha está vazia
    if (pilha->topo != NULL) {
        Vertice* v = pilha->topo;
        pilha->topo = v->downprox;
        return v;
    }
    return NULL;
}

// Função para criar e alocar espaço de memória
// para estrutura de cabeça de pilha
Pilha* criar_pilha(void) {
    Pilha* nova_pilha = (Pilha*)malloc(sizeof(Pilha));
    if (nova_pilha == NULL) {
        fprintf(stderr, "ERRO: Erro de alocação de memória em criar_pilha()\n");
        exit(-1);
    }
    nova_pilha->topo = NULL;
    return nova_pilha;
}

// Libera memória alocada de cabeça de pilha
void libera_pilha(Pilha* pilha) {
    free(pilha);
}

// Funções de fila

// Insere vértice em fila
void enqueue_vertice(Fila* fila, Vertice* vertice) {
    // caso de fila vazia
    if (fila->inicio == NULL) {
        fila->inicio = vertice;
        fila->fim = vertice;
        vertice->downprox = NULL;
    } else {
        fila->fim->downprox = vertice;
        fila->fim = vertice;
        vertice->downprox = NULL;
    }
}

// Remove vértice de fila
Vertice* dequeue_vertice(Fila* fila) {
    // verifica se fila está vazia
    if (fila->inicio != NULL) {
        Vertice* v = fila->inicio;
        // caso de fila com um elemento
        if (fila->inicio == fila->fim) 
            fila->inicio = fila->fim = NULL;
        else
            fila->inicio = fila->inicio->downprox;
        return v;
    }
    return NULL;
}

// Função para criar e alocar espaço de memória
// para estrutura de cabeça de fila
Fila* criar_fila(void) {
    Fila* nova_fila = (Fila*)malloc(sizeof(Fila));
    if (nova_fila == NULL) {
        fprintf(stderr, "ERRO: Erro de alocação de memória em criar_fila()\n");
        exit(-1);
    }
    nova_fila->inicio = NULL;
    return nova_fila;
}

// Libera memória alocada de cabeça de fila
void libera_fila(Fila* fila) {
    free(fila);
}


// Função de criação e alocação de memória  
// para a estrutura de grafo
Grafo* criar_grafo(int num_vertices) {
    if (num_vertices < 0) {
        fprintf(stderr, "ERRO: Grafo com quantidade negativa de vértices\n");
        return NULL;
    }   
    Grafo* novo_grafo = (Grafo*)malloc(sizeof(Grafo));
    if (novo_grafo == NULL) {
        fprintf(stderr, "ERRO: falha de alocação de memória em criar_grafo\n");
        exit(-1);
    }
    novo_grafo->ocupados = 0;
    novo_grafo->num_vertices = num_vertices;
    if (num_vertices == 0) {
        // não será alocada memória para o vetor de vértices
        novo_grafo->vertices = NULL;
        printf("Grafo vazio\n");
        return novo_grafo;
    }
    novo_grafo->vertices = (Vertice**)malloc(sizeof(Vertice*) * num_vertices);
    if (novo_grafo->vertices == NULL) {
        fprintf(stderr, "ERRO: falha de alocação de memória em criar_grafo\n");
        exit(-1);
    }
    for (int i = 0; i < num_vertices; i++)
        novo_grafo->vertices[i] = NULL;
    printf("Grafo criado e alocado com sucesso, com %d vértices\n", num_vertices);
    return novo_grafo;
}

// Insere um vértice na estrutura de grafo valor 
// deve ser inteiro de 0 a tamanho do grafo - 1
void inserir_vertice(int chave, char valor, Grafo* grafo) {
    if (grafo == NULL) {
        fprintf(stderr, "ERRO: grafo passado em inserir_vertice NULL\n");
        return;
    }
    if (chave > (grafo->num_vertices - 1) || chave < 0) {
        fprintf(stderr, "ERRO: valor inválido para vértice\n");
        return;
    }
    if (grafo->vertices[chave] != NULL) {
        fprintf(stderr, "ERRO: posição a ser inserida ocupada\n");
        return;
    }
    // cria novo vértice
    Vertice* novo_vertice = criar_vertice(chave, valor);
    // insere na posição adequada
    grafo->vertices[chave] = novo_vertice;
    // aumenta o número de ocupados
    grafo->ocupados++;
}

// Insere uma aresta na estrutura de grafo indo do vértice
// 'v1' para o vertice 'v2', com peso da aresta 'peso'
void inserir_aresta(int v1, int v2, int peso, Grafo* grafo) {
    Aresta* arestas1 = grafo->vertices[v1]->arestas;
    Aresta* arestas2 = grafo->vertices[v2]->arestas;
    // cria nova aresta
    Aresta* nova_aresta_v1 = criar_aresta(v2, peso);
    // se estrutura de arestas vazia, nova aresta cabeça
    // se não, insere ordenado
    if (arestas1 == NULL)
        grafo->vertices[v1]->arestas = nova_aresta_v1;
    else 
        grafo->vertices[v1]->arestas = inserir_ordenado_aresta(nova_aresta_v1, grafo->vertices[v1]->arestas, 0);
    // aumenta número de arestas do vértice
    grafo->vertices[v1]->num_arestas++;

    // cria nova aresta
    Aresta* nova_aresta_v2 = criar_aresta(v1, peso);
    // se estrutura de arestas vazia, nova aresta cabeça
    // se não, insere ordenado
    if (arestas2 == NULL)
        grafo->vertices[v2]->arestas = nova_aresta_v2;
    else
        grafo->vertices[v2]->arestas = inserir_ordenado_aresta(nova_aresta_v2, grafo->vertices[v2]->arestas, 0);
    // aumenta número de arestas do vértice
    grafo->vertices[v2]->num_arestas++;
}

// Libera toda a memória alocada pela estrutura de grafo
void libera_grafo(Grafo* grafo) {
    for (int i = 0; i < grafo->num_vertices; i++) {
        // inicializa cursores
        Aresta* prev = NULL;
        Aresta* a = grafo->vertices[i]->arestas;
        for (int j = 0; j < grafo->vertices[i]->num_arestas; j++) {
            prev = a;
            a = a->prox;
            // libera cada aresta
            free(prev);
        }
        // linera vértice
        free(grafo->vertices[i]);
    }
    // libera vetor de Vertice*
    free(grafo->vertices);
    // libera grafo
    free(grafo);
    printf("Memória liberada\n");
}

// Imprime todo o conteúdo de um grafo
void imprime_grafo(Grafo* grafo) {
    for (int i = 0; i < grafo->num_vertices; i++) {
        printf("Vértice: %d %c\n", grafo->vertices[i]->chave, grafo->vertices[i]->valor);
        Aresta* a = grafo->vertices[i]->arestas;
        for (int j = 0; j < grafo->vertices[i]->num_arestas; j++) {
            printf("Aresta %d, com vértice %d, peso %d\n", j, a->vertice2, a->peso);
            a = a->prox;
        }
    }
}

// Realiza um percurso em profundidade (DFS) em um grafo
void dfs(Grafo* grafo, int origem) {
    Vertice** vertices = grafo->vertices;

    // mantém relação dos vértices adicionados na pilha
    int adicionados[grafo->num_vertices];
    for (int i = 0; i < grafo->num_vertices; i++)
        adicionados[i] = 0;

    // cria estrutura auxiliar de pilha
    Pilha* aux_pilha = criar_pilha();

    // insere o primeiro vértice na pilha
    push_vertice(aux_pilha, vertices[origem]);
    adicionados[origem] = 1;

    while (aux_pilha->topo != NULL) {
        // retira o vértice corrente da pilha
        Vertice* aux_vertice = pop_vertice(aux_pilha);

        // imprime conteúdo do vértice
        printf("Chave: %d, Valor: %c\n", aux_vertice->chave, aux_vertice->valor);

        // ponteiro auxiliar para percorrer arestas
        Aresta* aux_aresta = aux_vertice->arestas;
        int num_arestas = aux_vertice->num_arestas;
        Aresta* aresta_ord = NULL;
        while (num_arestas--) {
            int vertice2 = aux_aresta->vertice2;
            // verifica se vertice já está presente
            if (adicionados[vertice2] == 0) {
                if (aresta_ord == NULL)
                    aresta_ord = criar_aresta(aux_aresta->vertice2, aux_aresta->peso);
                else {
                    Aresta* nova_aresta = criar_aresta(aux_aresta->vertice2, aux_aresta->peso);
                    aresta_ord = inserir_ordenado_aresta(nova_aresta, aresta_ord, 1);
                }
                adicionados[vertice2] = 1;
            }
            aux_aresta = aux_aresta->prox;
        }
        Aresta* a = NULL;
        for (a = aresta_ord; a != NULL; a = a->prox) {
            int vertice2 = a->vertice2;
            push_vertice(aux_pilha, vertices[vertice2]);
        }
        Aresta* prev = NULL;
        a = aresta_ord;
        while (a != NULL) {
            prev = a;
            a = a->prox;
            free(prev);
        }
    }

    // libera memória da cabeça de pilha
    libera_pilha(aux_pilha);
}

// Limpa os valores calculados na última execução do algoritmo
void reboot_dijkstra(Grafo* grafo) {
    for (int i = 0; i < grafo->num_vertices; i++)
        grafo->vertices[i]->menor_caminho = -1;
}

// Executa o algoritmo de Dijkstra, flag keep_values
// para chamar reboot ou não
void dijkstra_algorithm(Grafo* grafo, int origem, int keep_values) {
    Vertice** vertices = grafo->vertices;
    // relação de vértices visitados
    int visitados[grafo->num_vertices];
    for (int i = 0; i < grafo->num_vertices; i++)
        visitados[i] = 0;
    
    // relação de vértices adicionados
    int adicionados[grafo->num_vertices];
    for (int i = 0; i < grafo->num_vertices; i++)
        adicionados[i] = 0;

    // vértice de origem
    Vertice* v_origem = vertices[origem];

    // cria estrutura auxiliar de fila
    Fila* aux_fila = criar_fila();

    // insere vértice de origem na fila
    enqueue_vertice(aux_fila, v_origem);
    adicionados[origem] = 1;

    // inicializa distância até origem como 0
    v_origem->menor_caminho = 0;

    while (aux_fila->inicio != NULL) {
        // retira o vértice corrente
        Vertice* aux_vertice = dequeue_vertice(aux_fila);

        if (visitados[aux_vertice->chave] == 0) {
            Aresta* aux_aresta = aux_vertice->arestas;
            for (int i = 0; i < aux_vertice->num_arestas; i++) {
                int vertice2 = aux_aresta->vertice2;
                int peso = aux_aresta->peso;
                // se vértice já tem valor calculado, verifica se o novo é menor ou não
                if (vertices[vertice2]->menor_caminho != -1) {
                    if (aux_vertice->menor_caminho + peso < vertices[vertice2]->menor_caminho)
                        vertices[vertice2]->menor_caminho = aux_vertice->menor_caminho + peso;
                } else {
                    vertices[vertice2]->menor_caminho = aux_vertice->menor_caminho + peso;
                }
                // verifica se os vértices apontados pelas arestas já foram adicionados
                if (adicionados[vertice2] == 0) {
                    enqueue_vertice(aux_fila, vertices[vertice2]);
                    adicionados[vertice2] = 1;
                }
                aux_aresta = aux_aresta->prox;
            }
            visitados[aux_vertice->chave] = 1;
        }
    }

    // imprime os menores caminhos calculados
    for (int i = 0; i < grafo->num_vertices; i++) {
        printf("Menor caminho de %d para %d: %d\n", origem, i, vertices[i]->menor_caminho);
    }

    // libera estrutura de fila
    libera_fila(aux_fila);

    // verifica se deve ou não eliminar valores calculados
    if (!keep_values)
        reboot_dijkstra(grafo);
}
