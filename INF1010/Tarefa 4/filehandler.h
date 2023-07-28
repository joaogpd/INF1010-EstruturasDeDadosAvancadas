#ifndef TAREFA4INF1010_FILEHANDLER_H
#define TAREFA4INF1010_FILEHANDLER_H

typedef struct arrayoc arrayOc;
typedef struct codedict cdDict;

arrayOc* build_arrayOc(char* name, char* mode);
void print_binary(char* name, cdDict** codedict);

#endif //TAREFA4INF1010_FILEHANDLER_H
