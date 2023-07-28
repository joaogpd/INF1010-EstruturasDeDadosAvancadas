#include "arrayoc.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ASCII_LENGTH 128

/* Definições de tipos */

typedef struct arrayoc arrayOc;
struct arrayoc {
    int length;
    int* occurrences;
};

/* Funções internas */

/* Cria um array de inteiro de tamanho especificado */
int* create_intarray(int length) {
    if (length < 0) {
        fprintf(stderr, "create_intarray(): Valor de tamanho do array invalido\n");
        exit(-1);
    }
    int* new_intarray = (int*)malloc(sizeof(int) * length);
    if (new_intarray == NULL) {
        fprintf(stderr, "create_intarray(): Erro de alocacao de memoria\n");
        exit(-4);
    }
    for (int i = 0; i < length; i++)
        new_intarray[i] = 0;
    printf("create_intarray(): Novo array de inteiros criado com sucesso\n");
    return new_intarray;
}

/* Cria uma estrutura de array de ocorrencias que
 * contém um vetor de tamanho especificado
 */
arrayOc* create_arrayOc(int length) {
    arrayOc* new_arrayOc = (arrayOc*)malloc(sizeof(arrayOc));
    if (new_arrayOc == NULL) {
        fprintf(stderr, "create_arrayOc(): Erro de alocacao de memoria\n");
        exit(-4);
    }
    new_arrayOc->length = length;
    new_arrayOc->occurrences = create_intarray(length);
    printf("create_arrayOc(): Nova estrutura criada com sucesso\n");
    return new_arrayOc;
}

/* Insere um valor na posição adequada no array
 * de inteiros de ocorrencias
 */
void insert_arrayOc(arrayOc* head, char value) {
    if (head == NULL) {
        fprintf(stderr, "insert_arrayOc(): Valor de cabeca de array de ocorrencias invalido\n");
        exit(-1);
    }
    if (value > head->length || value < 0) {
    	fprintf(stderr, "insert_arrayOc(): Valor de valor a ser inserido invalido\n");
    	exit(-2);
    }
    head->occurrences[(int)value] += 1;
    printf("insert_arrayOc(): Valor %c incrementado em um com sucesso\n", value);
}

/* Funções de acesso */

/* Imprime todos os valores do array de ocorrencias recebido */
void print_arrayOc(arrayOc* head) {
    if (head == NULL) {
        fprintf(stderr, "print_arrayOc(): Valor de cabeca de estrutura invalido\n");
        exit(-1);
    }
    for (int i = 0; i < head->length; i++)
        printf("Posicao %d (char %c): %d\n", i, (char)i, head->occurrences[i]);
}

/* Acessa o valor de uma posição do array de ocorrencias
 * da estrutura recebida pela função
 */
int access_arrayOc(arrayOc* head, int position) {
    if (head == NULL) {
        fprintf(stderr, "access_arrayOc(): Valor de cabeca de array de ocorrencias invalido\n");
        exit(-1);
    }
    if (position < 0 && position > head->length) {
        fprintf(stderr, "access_arrayOc(): Valor de posicao da estrutura invalido\n");
        exit(-2);
    }
    return head->occurrences[position];
}

/* Extrai os caracteres de uma string e controi um
 * array de ocorrencias com base nisto
 */
arrayOc* extract_characters(char* string) {
    if (string == NULL) {
        fprintf(stderr, "extract_characters(): Valor de string invalida\n");
        exit(-1);
    }
    arrayOc* head = create_arrayOc(ASCII_LENGTH);
    for (int i = 0; i < strlen(string); i++)
        insert_arrayOc(head, string[i]);
    printf("extract_characters(): Array de ocorrencias construído e retornado com sucesso\n");
    return head;
}

/* Obtem o campo length de uma estrutura arrayOc */
int get_length(arrayOc* oc) {
    return oc->length;
}

/* Libera a memoria de uma estrutura de arrayOc. Primeiro,
 * do vetor interno de inteiros. Depois, da estrutura em si 
 */
void free_arrayOc(arrayOc* ao) {
    free(ao->occurrences);
    free(ao);
}
