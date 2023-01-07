#include "extractlcs.h"
#include<string.h>

void takeSize(FILE *fp,fileInfo *x){
    fseek(fp, 0L, SEEK_END);
    x->length=ftell(fp);
    rewind(fp);
}

void takeDataFromFile(FILE *fp, fileInfo *x ){
    char c;
    long int i=0;
    while ((c = getc(fp)) != EOF) {
        x->value[i] = c;
        i++;
    }
}

void readFileInfo(char *inputfile,fileInfo *x){
    FILE *fp = fopen(inputfile,"rb");
    if(fp == NULL){
        perror("File doesn't exists");
        exit(1);
    }
    takeSize(fp,x);
    x->value= malloc(x->length * sizeof(byte)+1);
    takeDataFromFile(fp,x);
    fclose(fp);
}
void allocateTable(lcsData *inProgressData){
    inProgressData->tableData = ( int **) malloc(inProgressData->a->length * sizeof(int*)+1);
    if(inProgressData->tableData == NULL) exit(1);
    for(long int i = 0; i < inProgressData->a->length+1; i++) {
        inProgressData->tableData[i] = (int *) malloc(inProgressData->b->length  * sizeof(int)+1);
        if(inProgressData->tableData[i] == NULL) exit(1);
    }

}

int max( int a,  int b){
    return a>b ? a: b;
}

void getLcs(lcsData *data){
    for (long i=0; i<=data->a->length; i++)
    {
        for (long j=0; j<=data->b->length; j++)
        {
            if (i == 0 || j == 0)
                data->tableData[i][j] = 0;
            else if (data->a->value[i-1] == data->b->value[j-1])
                data->tableData[i][j] = data->tableData[i-1][j-1] + 1;
            else
                data->tableData[i][j] = max(data->tableData[i-1][j], data->tableData[i][j-1]);
        }
    }
}

void printLcsResult(lcsData *data ){
    long i=data->a->length , j=data->b->length;
    int index = data->tableData[i][j];
    data->output= malloc(index * sizeof(byte));
    if(data->output == NULL){
        perror("not such memory");
        exit(1);
    }
    while (i > 0 && j > 0)
    {
        if (data->a->value[i-1] == data->b->value[j-1])
        {
            data->output[index-1] = data->a->value[i-1];
            i--; j--; index--;
        }
        else if (data->tableData[i-1][j] > data->tableData[i][j-1]) i--;
        else j--;
    }
}

void saveOutput(char *outputFile, lcsData *data){
    FILE *fp= fopen(outputFile,"wb");
    fwrite(data->output , 1 , sizeof(byte) * data->tableData[data->a->length][data->b->length], fp );
    fclose(fp);

}

void deallocData(lcsData *data){
    for(int i = 0; i < data->a->length; i++)
        free(data->tableData[i]);
    free(data->output);
    free(data->a->value);
    free(data->a);
    free(data->b->value);
    free(data->b);
    free(data->tableData);
}

void extractlcs(char *file1, char *file2, char *output){
    lcsData *inProgressData = malloc(sizeof(lcsData));
    inProgressData->a =malloc(sizeof(fileInfo));
    readFileInfo(file1,inProgressData->a);
    inProgressData->b =malloc(sizeof(fileInfo));
    readFileInfo(file2,inProgressData->b);
    allocateTable(inProgressData);
    getLcs(inProgressData);
    printLcsResult(inProgressData);
    saveOutput(output,inProgressData);
    deallocData(inProgressData);
}

