#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"
#include "queue.h"

/* Tipo estruturado de uma arvore binaria generica.
 * Possui campos de chave, e de referencias as subarvores
 * da direita e da esquerda
 */
typedef struct bintree BinTree;
struct bintree {
    int key;
    BinTree* left;
    BinTree* right;
};

/* Retorna NULL para representar um no vazio de uma arvore
 */
BinTree* cria_vazia_bt(void) {
    return NULL;
}

/* A funcao cria_bt cria um novo no da arvore, e o retorna.
 * Checagem de alocacao de memoria, e exibicao de mensagem
 * de erro adequada.
 */
BinTree* cria_bt(int key, BinTree* sae, BinTree* sad) {
    BinTree* novo = (BinTree*)malloc(sizeof(BinTree));
    if (novo == NULL) {
    	fprintf(stderr, "ERRO ALOCACAO MEMORIA");
	exit(1);
    }
    novo->left = sae;
    novo->right = sad;
    novo->key = key;
    return novo;
}


/* Insere um no na arvore b, de chave key.
 * Retorna a versao atualizada da arvore
 */
BinTree* insere_bt_q(BinTree* b, int key) {
    if (b == NULL) {
        b = cria_bt(key, NULL, NULL);
	return b;
    }
    Fila* f = cria_fila();
    insere_fila(f, b);
    while (!vazia_fila(f)) {
        BinTree* b2 = retira_fila(f);
 
        if (b2->left == NULL) {
            b2->left = cria_bt(key, NULL, NULL);
            f = libera_fila(f);
            return b;
        } else if (b2->right == NULL) {
            b2->right = cria_bt(key, NULL, NULL);
            f = libera_fila(f);
            return b;
        } else {
            if (b2->left != NULL)
                insere_fila(f, b2->left);
            if (b2->right != NULL)
                insere_fila(f, b2->right);
        }
    }
    f = libera_fila(f);
    return b;
}
/* A funcao verifica_bt verifica se uma arvore e ou nao uma
 * arvore binaria de busca, retornando 0 ou 1
 */
int verifica_bt(BinTree* b) {
    if (b != NULL) {
        if (b->right != NULL && b->key >= b->right->key) return 0;
        else if (b->left != NULL && b->key <= b->left->key) return 0;
        verifica_bt(b->right);
        verifica_bt(b->left);
    }
    return 1;
}

/* A funcao imprime_bt imprime os conteudos da arvore b em pre-
 * ordem
 */
void imprime_bt(BinTree* b) {
    printf("(");
    if (b != NULL) {
    	printf(" %d ", b->key);
	printf(" %p %p %p ", b, b->left, b->right);
	imprime_bt(b->left);
	imprime_bt(b->right);
    }
    printf(")");
}

/* A funcao altura_bt calcula a altura do maior ramo de uma arvore.
 * Retorna o valor dessa altura, com base em uma arvore b
 */
int altura_bt(BinTree* b) {
    if (b == NULL)
        return 0;
    else {
        int alt_left = altura_bt(b->left);
        int alt_right = altura_bt(b->right);

        return ((alt_left > alt_right) ? alt_left : alt_right) + 1;
    }
}

/* A funcao libera_bt libera a memoria alocada da arvore b
 * Ao final da execucao, retorna NULL
 */
BinTree* libera_bt(BinTree* b) {
    if (b == NULL) return NULL;
    else { 
        libera_bt(b->left);
	libera_bt(b->right);
        free(b);
    }
    return NULL;
}

/* A funcao troca_bt troca as subarvores direita e esquerda
 * da arvore. Recebe uma arvore b, e retorna uma arvore 
 * atualizada
 */
BinTree* troca_bt(BinTree* b) {
    if (b == NULL) return b;
    else {
        BinTree* temp = b->left;
	b->left = b->right;
	b->right = temp;
	troca_bt(b->left);
	troca_bt(b->right);
    }
    return b;
}
