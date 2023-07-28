#include "filehandler.h"
#include "arrayoc.h"
#include "priorityqueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_SIZE 1000

typedef struct arrayoc arrayOc;

/* Funções internas */

/* Extrai os conteúdos de um arquivo
 * para um array de char, e o retorna
 */
char *extract_lines(FILE *arq) {
  if (arq == NULL) {
    fprintf(stderr, "extract_lines(): Valor de arquivo inválido\n");
    exit(-1);
  }
  char *lines = (char *)malloc(sizeof(char) * (FILE_SIZE + 1));
  strcpy(lines, "");
  while (!feof(arq)) {
    char line[FILE_SIZE];
    fscanf(arq, "%[^\n]\n", line);
    strcat(lines, line);
  }
  return lines;
}

/* Realizar a abertura de um arquivo, retornando um
 * FILE* para o arquivo aberto
 */
FILE *open_file(char *name, char *mode) {
  if (name == NULL) {
    fprintf(stderr, "open_file(): Valor de nome do arquivo invalido\n");
    exit(-1);
  }
  if (mode == NULL) {
    fprintf(stderr, "open_file(): Valor de modo de abertura invalido\n");
    exit(-2);
  }
  FILE *arq = fopen(name, mode);
  if (arq == NULL) {
    fprintf(stderr, " open_file(): Erro na abertura do arquivo\n");
    exit(-10);
  }
  printf(" open_file(): Arquivo aberto com sucesso\n");
  return arq;
}

/* Fecha um arquivo
 */
void close_file(FILE *arq) {
  if (arq == NULL) {
    printf("close_file(): Arquivo de valor nulo, nada a fazer\n");
  }
  fclose(arq);
  arq = NULL;
  printf("close_file(): Arquivo fechado com sucesso\n");
}

/* Funções de acesso */

/* Constroi um array de ocorrencias dos
 * caracteres de um arquivo e o retorna
 */
arrayOc *build_arrayOc(char *name, char *mode) {
  if (name == NULL) {
    fprintf(stderr, "build_arrayOc(): Valor de nome do arquivo invalido\n");
    exit(-1);
  }
  if (mode == NULL) {
    fprintf(stderr, "build_arrayOc(): Valor de modo de abertura invalido\n");
    exit(-2);
  }
  FILE *char_arq = open_file(name, mode);
  char *lines = extract_lines(char_arq);
  arrayOc *occurrences = extract_characters(lines);
  free(lines);
  close_file(char_arq);
  return occurrences;
}

/* Imprime no terminal e em um arquivo binário o resultado da codificação
 * pelo algoritmo de Hufmann. Recebe o nome do arquivo de entrada e um
 * array de cdDict, que armazenam o código correspondente a cada letra
 */
void print_binary(char *name, cdDict **codedict) {
  FILE *char_arq = open_file(name, "r");
  FILE *char_bin = open_file("output.bin", "wb");
  char *code = (char *)malloc(sizeof(char) * 8);
  unsigned short bitmask = 0;
  int bitmask_counter = 0;
  while (!feof(char_arq)) {
    char arq_char = fgetc(char_arq);
    if (arq_char != '\n') {
      accessDict(codedict, (int)arq_char, code);
      printf("%s", code);
      int len = strlen(code);
      // caso vá ultrapassar os 16 bits do short, imprime o valor atualmente
      // armazenado e volta valor de bitmask para zero. Acrescenta certa
      // quantidade de padding evitável, mas diminui o tamanho do arquivo de
      // entrada consideravelmente (de 99 para 30 bytes, no caso do enunciado)
      if (bitmask_counter + len >= 16) {
        fwrite(&bitmask, sizeof(unsigned char), 1, char_bin);
        bitmask_counter = 0;
      }
      for (int i = 0; i < len; i++) {
        bitmask = (bitmask << bitmask_counter) | ((char)code[i] - '0');
      }
      bitmask_counter += len;
    }
  }
  printf("\n");
  free(code);
  close_file(char_bin);
  close_file(char_arq);
}
