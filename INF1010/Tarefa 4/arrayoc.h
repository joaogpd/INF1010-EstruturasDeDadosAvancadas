#ifndef TAREFA4INF1010_ARRAYOC_H
#define TAREFA4INF1010_ARRAYOC_H

typedef struct arrayoc arrayOc;

arrayOc* extract_characters(char* string);
int access_arrayOc(arrayOc* head, int position);
void print_arrayOc(arrayOc* head);
int get_length(arrayOc* oc);
void free_arrayOc(arrayOc* ao);

#endif //TAREFA4INF1010_ARRAYOC_H
