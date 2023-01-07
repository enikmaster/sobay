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

#endif