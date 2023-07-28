// Nota 9.8 de 10

#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"
#include "binstree.h"
#include "execution.h"

int main(void) {
    // geracao de numeros aleatorios
    int* rand_numbers = rand_nums(20, 10);

    // insercao nas duas arvores binarias (generica e de
    // busca, respectivamente)
    BinTree* bt_tree = insert_level(rand_numbers, 10);
    BinSTree* bst_tree = insert_bst(rand_numbers, 10);

    // impressao das duas arvores em seu estado inicial 
    // (logo apos a criacao)
    printf("IMPRESSAO INICIAL ARVORE 1:\n");
    imprime_bt(bt_tree);
    printf("\n");
    printf("IMPRESSAO INICIAL ARVORE 2:\n");
    imprime_bst(bst_tree);
    printf("\n");

    // verificacao se as arvores sao ou nao de busca. a primeira, generica
    // muito provavelmente nao sera de busca (embora nao seja impossivel).
    // a segunda sempre deve ter resultado positivo
    printf("binaria de busca?\narvore 1 (bt): %d\narvore 2 (bst): %d\n",
		    verifica_bt(bt_tree), 
		    verifica_bst(bst_tree));

    // leitura da altura de cada uma das duas arvores. A altura da primeira
    // devera ser sempre fixa, 4, enquanto a segunda pode ter altura
    // variavel (a depender dos numeros gerados)
    printf("altura?\narvore 1 (bt): %d\narvore 2 (bst): %d\n",
		    altura_bt(bt_tree),
		    altura_bst(bst_tree));

    // troca os nos das arvores da subarvore direita para a subarvore
    // esquerda, para todos os nos
    bt_tree = troca_bt(bt_tree);
    bst_tree = troca_bst(bst_tree);

    // imprime o novo estado das arvores apos a troca
    printf("IMPRESSAO APOS TROCA ARVORE 1:\n");
    imprime_bt(bt_tree);
    printf("\n");
    printf("IMPRESSAO APOS TROCA ARVORE 2:\n");
    imprime_bst(bst_tree);
    printf("\n");

    // nova verificacao. agora, a segunda deve obrigatoriamente ter resultado
    // negativo, visto que tem a logica inversa de uma arvore de busca
    printf("binaria de busca?\narvore 1 (bt): %d\narvore 2 (bst): %d\n",
		    verifica_bt(bt_tree), 
		    verifica_bst(bst_tree));

    // liberacao de memoria das arvores e do array dos numeros
    // gerados aleatoriamente
    bt_tree = libera_bt(bt_tree);
    bst_tree = libera_bst(bst_tree);

    free(rand_numbers);
    return 0;
}
