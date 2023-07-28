#ifndef BINTREE_H
#define BINTREE_H

typedef struct bintree BinTree;
typedef struct fila Fila;

/* Retorna NULL para representar no vazio */
BinTree* cria_vazia_bt(void);
/* Retorna um no.
 * Recebe as subarvores a direita, a esquerda, e uma chave
 */
BinTree* cria_bt(int key, BinTree* sae, BinTree* sad);
/* Verifica se a arvore b e binaria de busca */
int verifica_bt(BinTree* b);
/* Insere um no na arvore
 * Recebe uma arvore e uma chave
 */
BinTree* insere_bt_q(BinTree* b, int key);
/* Imprime os conteudos da arvore */
void imprime_bt(BinTree* b);
/* Retorna a altura da arvore */
int altura_bt(BinTree* b);
/* Libera a memoria alocada de uma arvore
 * Retorna NULL
 */
BinTree* libera_bt(BinTree* b);
/* Troca as subarvores direita e esquerda de uma arvore */
BinTree* troca_bt(BinTree* b);

#endif
