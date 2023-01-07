#ifndef EMANUELEGURINI105916_EXTRACTLCS_H
#define EMANUELEGURINI105916_EXTRACTLCS_H
#include "stdlib.h"
#include "stdio.h"
typedef unsigned char byte;
typedef struct fileInfo{
    byte *value;
    long int length;
}fileInfo;

typedef struct lcsData{
    fileInfo *a;
    fileInfo *b;
    int **tableData;
    byte *output;
}lcsData;


void extractlcs(char *file1, char *file2, char *output);

#endif //EMANUELEGURINI105916_EXTRACTLCS_H
