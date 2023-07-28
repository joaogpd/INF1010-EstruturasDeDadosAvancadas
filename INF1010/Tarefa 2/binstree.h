#ifndef BINSTREE_H
#define BINSTREE_H

typedef struct binstree BinSTree;

/* Retorna NULL para representar a criacao */
BinSTree* cria_bst(void);
/* Cria um no de arvore binaria de busca, de pai y e chave key */
BinSTree* cria_no_bst(BinSTree* y, int key);
/* Insere um no na arvore 
 * Recebe uma arvore e uma chave
 */
BinSTree* insere_bst(BinSTree* y, BinSTree* b, int key);
/* Imprime o conteudo da arvore */
void imprime_bst(BinSTree* b);
/* Verifica se a arvore e binaria */
int verifica_bst(BinSTree* b);
/* Retorna a altura da arvore */
int altura_bst(BinSTree* b);
/* Libera a memoria alocada de uma arvore
 * Retorna NULL
 */
BinSTree* libera_bst(BinSTree* b);
/* Troca as subarvores direita e esquerda de uma arvore */
BinSTree* troca_bst(BinSTree* b);

#endif
