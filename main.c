#include<stdio.h>
#include<stdlib.h>
#include "extractlcs.h"
int main(int argc , char *argv[]){
    if(argc == 4) extractlcs(argv[1],argv[2],argv[3]);
    else exit(1);
    return 0;
}

