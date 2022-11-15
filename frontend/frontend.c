#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "frontend.h"
#include "frontendFunctions.c"


int main (int argc, char **argv) {

    int verificaLogin = 1; // 0 -> Se a operação for autorizada pelo backend // 1 -> se for rejeitado

    if(argc < 3 || verificaLogin == 0) {
        printf("Dados incorretos.");
        return 1;
    }

    int v = 0;

    int pid = getpid();
    printf("Bem vindo, %s!\n", argv[1]);

    do {
        v = userInput(pid);
    } while (v == 0);

    return 0;

}