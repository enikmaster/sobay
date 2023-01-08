#ifndef FRONTEND_H
#define FRONTEND_H

#include <stdio.h>
#include "constantes.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include "common.h"


typedef struct utilizadorLogin {
    comando comando;
    char username[TAM];
    char pwd[TAM];
    char fifoname[TAM];
    struct utilizadorLogin * seguinte;
} utilizadorLogin;

typedef struct utilizadorSell {
    comando comando;
    int id;
    char titulo[TAM];
    char categoria[TAM];
    int valorAtual;
    int compreJa;
    int tempo;
    char seller[TAM];
    char bidder[TAM];
    struct item* next;
} utilizadorSell;

typedef struct {
    char fifoname[TAM];
    char username[TAM];
}TDADOS_FRONT;

typedef struct {
    comando comando;
    char username[TAM];
} utilizadorList;

typedef struct {
    comando comando;
    char username[TAM];
    char str[TAM];
    int i;
} utilizadorLi_;


int userInput(char* user, int pid);

int userExit(int pid);

void userSell(char* user, char* nItem, char* categoria, int precoBase, int precoCompreJa, int tempo );

void userList(char* user);

void userLicat(char* user, char* categoria);

void userLiSel(char* user, char* username);

void userLiVal(char* user, int precoMax);

void userLiTime(char* user, int tempo);

void userTime(int pid);

void userBuy(int pid, int itemID, int valor);

void userCash(int pid);

void userAdd(int pid, int valor);




// THREADS

void* receive(void* dados);
void* cmdInput(void* dados);

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