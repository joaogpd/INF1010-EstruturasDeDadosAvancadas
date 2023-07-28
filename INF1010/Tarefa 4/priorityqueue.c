#include "priorityqueue.h"
#include "arrayoc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct codedict cdDict;
typedef struct priorityqueue pQ;
typedef struct node Node;

/* Tipo de cabeca de fila de prioridades, também 
 * usado como cabeça de binary tree
 */
struct priorityqueue {
    int tam;
    Node* first;
};

/* Tipo de no de fila de prioridade e de arvore binaria */
struct node {
    int val;
    char let;
    Node* pai;
    Node* right;
    Node* prox;
    Node* left;
};

/* Tipo de estrutura de codificacao de caracter */
struct codedict {
    char code[8];
    char let; 
};


/* Aloca memoria para um nó generico de arvore binaria
 * ou fila de prioridade e retorna o endereço associado
 */
Node* create_node(int val, char let, Node* pai, Node* right, Node* prox, Node* left) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(-4);
    }
    new_node->val = val;
    new_node->let = let;
    new_node->pai = pai;
    new_node->right = right;
    new_node->prox = prox;
    new_node->left = left;
    return new_node;
}

/* Aloca memoria para uma cabeça de fila de prioridades */
pQ* create_pq(void) {
    pQ* new_pq = (pQ*)malloc(sizeof(pQ));
    if (new_pq == NULL) {
        exit(-4);
    }
    new_pq->tam = 0;
    new_pq->first = NULL;
    return new_pq;
}

/* Insere um valor, com letra correspondente, em uma fila de prioridades */
void insert_pq(pQ* pq, int val, char let) {
    if (pq == NULL) {
        fprintf(stderr, "insert_pqueue(): Valor de cabeca de fila de prioridades invalido\n");
        exit(-1);
    }
    // cria novo nó
    Node* new_node = create_node(val, let, NULL, NULL, NULL, NULL);
    pq->tam++;
    // inicializa um nó 'cursor' para percorrer fila
    Node* current_node = pq->first;
    // caso primeiro nó NULL, lista vazia, cabeça aponta para novo nó
    if (current_node == NULL) {
        pq->first = new_node;
        printf("insert_pqueue(): Valor inserido na lista inicialmente vazia com sucesso\n");
        return;
    }
    // nó anterior NULL, inicialmente
    Node* prev_node = NULL;
    // percorre até fim da fila (tamanho)
    for (int i = 0; i < pq->tam - 1; i++) {
        // caso elemento seja maior, inserir no prévio
        if (current_node->val > val) {
            // se prévio NULL, elemento primeiro da fila
            if (prev_node == NULL) {
                new_node->prox = current_node;
                pq->first = new_node;
                printf("insert_pqueue(): Valor inserido na lista como primeiro elemento com sucesso\n");
                return;
            }
            // caso contrário, inserir na posição adequada
            prev_node->prox = new_node;
            new_node->prox = current_node;
            printf("insert_pqueue(): Valor inserido na lista com sucesso\n");
            return;
        }
        // continuar busca
        prev_node = current_node;
        current_node = current_node->prox;
    }
    // elemento na última posição
    prev_node->prox = new_node;
    printf("insert_pqueue(): Valor inserido na lista na ultima posicao com sucesso\n");
    return;
}

/* Insere um no diretamente em vez de um valor (novo nó criado nesse caso) */
void insert_pq_node(pQ* pq, Node* node) {
    if (pq == NULL) {
        fprintf(stderr, "insert_pqueue(): Valor de cabeca de fila de prioridades invalido\n");
        exit(-1);
    }
    Node* new_node = node;
    pq->tam++;
    // inicializa um nó 'cursor' para percorrer fila
    Node* current_node = pq->first;
    // caso primeiro nó NULL, lista vazia, cabeça aponta para novo nó
    if (current_node == NULL) {
        pq->first = new_node;
        printf("insert_pqueue(): Valor inserido na lista inicialmente vazia com sucesso\n");
        return;
    }
    // nó anterior NULL, inicialmente
    Node* prev_node = NULL;
    // percorre até fim da fila (tamanho)
    for (int i = 0; i < pq->tam - 1; i++) {
        // caso elemento seja maior, inserir no prévio
        if (current_node->val > node->val) {
            // se prévio NULL, elemento primeiro da fila
            if (prev_node == NULL) {
                new_node->prox = current_node;
                pq->first = new_node;
                printf("insert_pqueue(): Valor inserido na lista como primeiro elemento com sucesso\n");
                return;
            }
            // caso contrário, inserir na posição adequada
            prev_node->prox = new_node;
            new_node->prox = current_node;
            printf("insert_pqueue(): Valor inserido na lista com sucesso\n");
            return;
        }
        // continuar busca
        prev_node = current_node;
        current_node = current_node->prox;
    }
    // elemento na última posição
    if (prev_node != NULL) {
        prev_node->prox = new_node;
        printf("insert_pqueue(): Valor inserido na lista na ultima posicao com sucesso\n");
    }
    return;
}

/* Remove o primeiro nó de uma fila de prioridades e o retorna */
Node* remove_pq(pQ* pq) {
    if (pq->first == NULL) {
        return NULL;
    }
    pq->tam--;
    Node* temp = pq->first;
    pq->first = pq->first->prox;
    return temp;
}

/* Libera a memoria de uma fila de prioridades */
void free_pq(pQ* pq) {
    if (pq->first == NULL) {
        exit(-1);
    }
    Node* ant = NULL;
    Node* node = pq->first;
    while (node != NULL) {
        ant = node;
        node = node->prox;
        free(ant);
    }
    free(pq);
}

/* Imprime os conteudos de uma fila de prioridades */
void print_pq(pQ* pq) {
    Node* node = pq->first;
    for (int i = 0; i < pq->tam; i++, node = node->prox)
        printf("%d, %c na posicao %d\n", node->val, node->let, i);
}

/* Imprime o conteúdo de um nó de fila de prioridades */
void print_node(Node* node) {
    if (node == NULL) {
        printf("NULL\n");
        return;
    }
    printf("node->val: %d, node->let: %c\n", node->val, node->let);
}

/* Converte um array de ocorrencias para uma fila de prioridades e a retorna */
pQ* convert_ao_pq(arrayOc* oc) {
    pQ* new_pq = create_pq();
    for (int i = 0; i < get_length(oc); i++) {
        if (access_arrayOc(oc, i) != 0)
            insert_pq(new_pq, access_arrayOc(oc, i), (char)i);
    }
    return new_pq;
}

/* Converte uma mesma estrutura de fila de prioridades para arvore binaria */
void pq_to_bt(pQ* pq) {
    while (pq->tam > 1) {
        Node* left = remove_pq(pq);
        Node* right = remove_pq(pq);

        Node* novo = create_node(left->val + right->val, '+', NULL, right, NULL, left);
        insert_pq_node(pq, novo);
    }
}

/* Imprime os conteúdos de uma árvore binária */
void print_btree(Node* node) {
    printf("(");
    if (node != NULL) {
        printf("%d, %c ", node->val, node->let);
        print_btree(node->left);
        print_btree(node->right);
    }
    printf(")");
}

/* Libera o conteudo de uma arvore binaria */
void free_btree(Node* node) {
    if (node != NULL) {
        free_btree(node->left);
        free_btree(node->right);
        free(node);
    }
}

/* chama free_btree sem quebrar encapsulamento */
void free_head(pQ* pq) {
    free_btree(pq->first);
    free(pq);
}

/* chama print_btree sem quebrar encapsulamento */
void print_head(pQ* pq) {
    if (pq == NULL)
        exit(-1);
    print_btree(pq->first);
}

/* Aloca memoria e cria um struct cdDict */
cdDict* create_cddict(int i) {
    cdDict* new_cddict = (cdDict*)malloc(sizeof(cdDict));
    if (new_cddict == NULL) 
        exit(-1);
    strcpy(new_cddict->code, "");
    new_cddict->let = (char)i;
    return new_cddict;
}

/* Realiza o percurso de uma arvore binaria para obter a codificacao
 * referente a cada letra presente no arquivo de entrada
 */
void percurso_btree(cdDict** dict, Node* node, char* code) {
    if (node->left == NULL && node->right == NULL) {
        int index = (int)node->let;
        dict[index]->let = node->let;
        strcpy(dict[index]->code, code);
        strcpy(code, "");
        return;
    }
    char code_aux[8];
    strcpy(code_aux, "");
    strcpy(code_aux, code);
    strcat(code_aux, "0");
    percurso_btree(dict, node->left, code_aux);
    strcpy(code_aux, code);
    strcat(code_aux, "1");
    percurso_btree(dict, node->right, code_aux);
}

/* chama percurso_btree sem quebrar o encapsulamento */
cdDict** percurso_head(pQ* pq) {
    if (pq == NULL)
        exit(-1);
    cdDict** new_cddictarray = (cdDict**)malloc(sizeof(cdDict*) * 128);
    for (int i = 0; i < 128; i++)
        new_cddictarray[i] = create_cddict(i);
    char code[8] = "";
    percurso_btree(new_cddictarray, pq->first, code);
    return new_cddictarray;
}

/* Imprime os conteúdos de um array de cdDict */
void print_cdDict(cdDict** cddict) {
    for (int i = 0; i < 128; i++) {
        if (strcmp("", cddict[i]->code) != 0)
            printf("%c %c: %s\n", cddict[i]->let, (char)i, cddict[i]->code);
    }
}

/* Imprime o conteúdo de um nó de cdDict */
void print_cdDict_one(cdDict** cddict, int i) {
    if (i < 128 && i >= 0) {
        printf("%s", cddict[i]->code);
    }
}

/* Acessa o conteúdo do codigo de um cdDict e retorna
 * por parâmetro para o argumento passado code
 */
void accessDict(cdDict** codedict, int i, char* code) {
    if (i >= 0 && i < 128) {
        strcpy(code, codedict[i]->code);
    }
}

/* Libera a memoria alocada de um vetor de cdDict */
void free_cdDict(cdDict** cddict) {
    for (int i = 0; i < 128; i++) {
        free(cddict[i]);
    }
    free(cddict);
}
