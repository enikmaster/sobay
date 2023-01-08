#ifndef COMMON_H
#define COMMON_H

#define BACKEND "BACKEND"

#include "constantes.h";

typedef enum{
    noCMD,
    login,
    sell,
    list,
    licat,
    lisel,
    lival,
    litime,
    timeP,
    buy,
    cash,
    add,
    exitP
} comando;

typedef struct {
    char titulo[TAM];
    char categoria[TAM];
    int precoBase;
    int precoCompreJa;
    int duracao;
    int id;
} listItem;


typedef struct{
    comando cmd;
    int i;
    char str[TAM];
    int quantItens;
    listItem itens[30];
} responseToFrontend;


#endif