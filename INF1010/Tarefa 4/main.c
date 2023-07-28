// Nota 10 de 10

#include <stdio.h>
#include "priorityqueue.h"
#include "arrayoc.h"
#include "filehandler.h"


int main(void) {
    arrayOc* teste_ao = build_arrayOc("input.txt", "r");
    printf("Array para contar ocorrencias de cada caracter: \n\n");
    print_arrayOc(teste_ao);

    printf("\n\n");

    pQ* teste_pq = convert_ao_pq(teste_ao);
    free_arrayOc(teste_ao);

    pq_to_bt(teste_pq);

    cdDict** new_cddictarray = percurso_head(teste_pq);

    printf("Dicionário de equivalência de cada caracter e sua codificacao: \n\n");

    print_cdDict(new_cddictarray);

    printf("\n\n");

    printf("Árvore binária representativa do algoritmo: \n\n");

    print_head(teste_pq);
    printf("\n\n");

    printf("Resultado da codificacao, impresso no terminal: \n\n");
    print_binary("input.txt", new_cddictarray);

    free_head(teste_pq);
    free_cdDict(new_cddictarray);
    return 0;
}