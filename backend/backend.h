#ifndef BACKEND_H
#define BACKEND_H

typedef struct user User, *pUser;
struct user {
	int pid;
	char nome[TAM];
	int saldo;
	pUser next;
};

int adminInput();
void checkUsers();
void cmdCheck(const int argNum, const char* cmd, const char* arg);

#endif