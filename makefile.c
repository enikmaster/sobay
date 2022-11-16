#include <stdio.h>
#include <string.h>
#include "makefile.h"

int main(int argc, char **argv) {

    if(argc != 2) {
        printf("Número de argumentos inválido!\n");
        return 1;
    }

    if(strcmp(argv[1], "clean") == 0)
        printf("O utilizador quer apagartodos os ficheiros temporários de apoio à compilação\n");
    else if (strcmp(argv[1], "frontend") == 0)
        printf("O utilizador quer compilar o programa frontend\n");
    else if (strcmp(argv[1], "backend") == 0)
        printf("O utilizador quer compilar o programa backend\n");
    else if (strcmp(argv[1], "all") == 0) {
        printf("O utilizador quer compilar todos os programas\n");
    } else
        printf("Argumento inválido.\n");


    return 0;
}