#ifndef EXECUTION_H
#define EXECUTION_H

typedef struct bintree BinTree;
typedef struct binstree BinSTree;

/* Gera um array de n inteiros de maior inteiro possivel max */
int* rand_nums(int max, int n);
/* Retorna uma arvore binaria com nos inseridos por nivel
 * a partir do array nums
 */
BinTree* insert_level(int* nums, int n);
/* Retorna uma arvore binaria de busca com nos inseridos
 * a partir do array nums
 */
BinSTree* insert_bst(int* nums, int n);

#endif
