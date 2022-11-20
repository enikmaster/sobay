#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../constantes.h"
#include "backend.h"
#include "users_lib.h"

int adminInput() {
	char str[TAM];
	do {
		puts("O que pretende testar?");
		fgets(str, TAM, stdin);
		int cnt = 0;
		for (int i = 0; i < strlen(str); ++i) {
			if (str[i] == ' ')
				++cnt;
		}
		if (cnt <= 0 && strlen(str)-1 <= 0) {
			puts("Nada foi escrito");
		} else if (cnt >= 2) {
			puts("Demasiados argumentos");
		} else {
			char cmd[TAM], arg[TAM];
			int argNum = sscanf(str, "%s %s", cmd, arg);
			cmdCheck(argNum, cmd, arg);
		}
	} while(strlen(str) > 1);
	return 0;
}

void checkUsers() {
	char username[TAM];
	puts("Indique um user:");
	scanf( "%s", username);
	if(getUserBalance(username) != -1) {
		int updatedBalance = updateUserBalance(username, getUserBalance(username)-1);
		if(updatedBalance == -1)
			puts("Erro ao atualizar saldo");
		else
			puts("Saldo atualizado");
			printf("saldo atual: %d", getUserBalance(username));
	}
	
}

void cmdCheck(const int argNum, const char* cmd, const char* arg) {
	if(strcmp(cmd, "users") == 0) // users - listar todos os clientes a usar a plataforma
		(argNum-1 != 0) ? puts("Este comando nao recebe argumentos...") : printf("Comando %s validado.\n", cmd);
	else if(strcmp(cmd, "list") == 0) // list - listar intes à venda(<id> <nome-item> <categoria> <preço-atual> <compre-ja> <seller> <higher-bider ou '-' >)
		(argNum-1 != 0) ? puts("Este comando nao recebe argumentos...") : printf("Comando %s validado.\n", cmd);
	else if(strcmp(cmd, "kick") == 0) // kick <username> - banir um cliente atualmente logado, como se o cliente tivesse feito logout
		(argNum-1 != 1) ? puts("Este comando precisa de 1 argumento...") : printf("Comando %s validado.\n", cmd);
	else if(strcmp(cmd, "prom") == 0) // prom - listar os promotores atualmente ativos
		(argNum-1 != 0) ? puts("Este comando nao recebe argumentos...") : printf("Comando %s validado.\n", cmd);
	else if(strcmp(cmd, "reprom") == 0) // reprom - atualizar os promotores, lê o ficheiro dos promotores novamente, encerrando os que deixaram de estar no ficheiro, carrega os novos, mantém inalterados os restantes
		(argNum-1 != 0) ? puts("Este comando nao recebe argumentos...") : printf("Comando %s validado.\n", cmd);
	else if(strcmp(cmd, "cancel") == 0) // cancel <nome-do-executavel-do-promotor> - cancela um promotor, deixa de estar em execução
		(argNum-1 != 1) ? puts("Este comando precisa de 1 argumentos...") : printf("Comando %s validado.\n", cmd);
	else if(strcmp(cmd, "close") == 0) // close - encerra a plataforma, avisando todos
		(argNum-1 != 0) ? puts("Este comando nao recebe argumentos...") : printf("Comando %s validado.\n", cmd);
	else
		printf("Comando '%s' desconhecido\n", cmd);
}