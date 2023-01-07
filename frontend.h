#ifndef FRONTEND_H
#define FRONTEND_H

#include <stdio.h>
#include "constantes.h"
#include "common.h"


typedef struct utilizadorLogin {
    comando comando;
    char username[TAM];
    char pwd[TAM];
    char fifoname[TAM];
} utilizadorLogin;

int userInput(int pid);

int userExit(int pid);

void userSell(int pid, char* nItem, char* categoria, int precoBase, int precoCompreJa, int tempo );

void userList(int pid);

void userLicat(int pid, char* categoria);

void userLiSel(int pid, char* username);

void userLiVal(int pid, int precoMax);

void userLiTime(int pid, int tempo);

void userTime(int pid);

void userBuy(int pid, int itemID, int valor);

void userCash(int pid);

void userAdd(int pid, int valor);

#endif
//comandos frontend
// sell
// list
// licat
// lisel
// lival
// litime
// time
// buy
// cash
// add
// exit