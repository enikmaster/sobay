#ifndef BACKEND_H
#define BACKEND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include "common.h"
#include "constantes.h"

#define TAM 256
typedef struct user User, *pUser;
struct user {
	int pid;
	char nome[TAM];
	int saldo;
	pUser next;
};

typedef struct item {
    int id;
    char titulo[TAM];
    char categoria[TAM];
    int valorAtual;
    int compreJa;
    int tempo;
    char seller[TAM];
    char bidder[TAM];
    struct item* next;
} item;

typedef struct utilizadorLogin {
    char username[TAM];
    char pwd[TAM];
    char fifoname[TAM];
    struct utilizadorLogin * seguinte;
} utilizadorLogin;

typedef struct utilizadorSell {
    char user[TAM];
    char item[TAM];
    char categoria[TAM];
    int precoBase;
    int precoCompreJa;
    int duracao;
} utilizadorSell;

typedef struct {
    char username[TAM];
} utilizadorList;

typedef struct {
    char username[TAM];
    char str[TAM];
    int i;
} utilizadorLi_;


int adminInput();
void cmdCheck(const int argNum, const char* cmd, const char* arg);
void lancaPromotores(char* fileName);
void stopPromotor(int x,siginfo_t* i, void* v);
struct item* recebeItems(struct item* itemptr);
void showItens(struct item* itemptr);
void checkUsers();
void cmdCheck(const int argNum, const char* cmd, const char* arg);

typedef struct
{
    utilizadorLogin* online;
    pthread_mutex_t mutex;
    item* itens;
}TDADOS; 

void findFifo(utilizadorLogin* online, char* user, char * f);

void *receive();
void *TadminInput(item* listaItens);

#endif