#ifndef QUEUE_H
#define QUEUE_H

/* Tipo estruturado no */
typedef struct no No;
/* Tipo estruturado fila */
typedef struct fila Fila;
/* Tipo estruturado no de arvore
 * binaria generica
 */
typedef struct bintree BinTree;

// Cria uma fila
Fila* cria_fila(void);
// Verifica se a fila esta vazia
int vazia_fila(Fila* f);
// Insere um no no fim da fila
void insere_fila(Fila* f, BinTree* b);
// Retira um no do inicio da fila e retorna
// seus dados
BinTree* retira_fila(Fila* f);
// Libera a memoria alocada da fila
Fila* libera_fila(Fila* f);

#endif
