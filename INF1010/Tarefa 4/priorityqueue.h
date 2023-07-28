#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include <stdio.h>

typedef struct priorityqueue pQ;
typedef struct node Node;
typedef struct arrayoc arrayOc;
typedef struct codedict cdDict;


pQ* create_pq(void);
void insert_pq(pQ* pq, int val, char let);
Node* create_node(int val, char let, Node* pai, Node* right, Node* prox, Node* left);
void insert_pq_node(pQ* pq, Node* node);
Node* remove_pq(pQ* pq);
void print_node(Node* node);
void free_pq(pQ* pq);
pQ* convert_ao_pq(arrayOc* oc);
void print_pq(pQ* pq);
void pq_to_bt(pQ* pq);
void print_head(pQ* pq);
void free_head(pQ* pq);
void print_cdDict(cdDict** cddict);
void print_cdDict_one(cdDict** cddict, int i);
void accessDict(cdDict** codedict, int i, char* code);
cdDict** percurso_head(pQ* pq);
void free_cdDict(cdDict** cddict);

#endif