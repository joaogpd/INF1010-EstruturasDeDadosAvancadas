#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/* typedef para execucao do programa */
typedef struct bintree BinTree;

/* tipo estruturado de no de fila. Tem como
 * campos dados, que sao um no de arvore binaria
 * e um next, que e o proximo elemento da fila
 */
typedef struct no No;
struct no {
    BinTree* data;
    No* next;
};

/* Tipo estruturado de fila. Guarda referencias
 * para os primeiro e ultimo nos da fila.
 */
typedef struct fila Fila;
struct fila {
    No* ini;
    No* fim;
};

/* Aloca memoria de um Fila*, poe os campos ini e fim como NULL */
Fila* cria_fila(void) {
    Fila* novo = (Fila*)malloc(sizeof(Fila));
    if (novo == NULL) {
        fprintf(stderr, "ERRO ALOCACAO MEMORIA");
	exit(1);
    }
    novo->ini = novo->fim = NULL;
    return novo;
}

/* Ve se uma fila esta vazia e retorna 0 ou 1 */
int vazia_fila(Fila* f) {
    return (f->ini == NULL);
}

/* Insere um no numa fila f, com data = b
 * Checa se a fila esta vazia, insere no final
 * se nao
 */
void insere_fila(Fila* f, BinTree* b) {
    No* novo_no = (No*)malloc(sizeof(No));
    if (novo_no == NULL) {
        fprintf(stderr, "ERRO ALOCACAO MEMORIA");
	exit(1);
    }
    novo_no->data = b;
    novo_no->next = NULL;
    if (f->ini == NULL) {
	f->ini = f->fim = novo_no;
	return;
    }
    f->fim->next = novo_no;
    f->fim = novo_no;
}

/* Retira um no da fila e retorna o campo data 
 * como é uma fila, o primeiro é retirado
 */
BinTree* retira_fila(Fila* f) {
    if (f->ini == NULL) 
        return NULL;
    No* temp = f->ini;
    BinTree* bt_node = f->ini->data;
    f->ini = f->ini->next;
    if (f->ini == NULL) 
	f->fim = NULL;
    free(temp);
    return bt_node;
}

/* Libera a memoria alocada do Fila* f 
 * Retorna NULL apos a liberacao de memoria
 */
Fila* libera_fila(Fila* f) {
    No* r = NULL;
    No* p = f->ini;
    while (p != NULL) {
        r = p;
	p = p->next;
	free(r);
    }
    free(f);
    return NULL;
}
