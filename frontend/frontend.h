#ifndef FRONTEND_H
#define FRONTEND_H

#define MAX_INPUT 256

#include <stdio.h>

struct utilizador {
    char username[MAX_INPUT];
    char pwd[MAX_INPUT];
};

typedef struct utilizador utilizador;

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