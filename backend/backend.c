#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../constantes.h"
#include "backend.h"
#include "users_lib.h"

void main(int argc, char** argv) {

	struct item* listaItens = NULL;
	listaItens =  recebeItems(listaItens);
	// showItens(listaItens);

	// verificação de backend já em execução
	puts("Bem-vindo administrador");
	int loadUsers = loadUsersFile(USER_PATH);
	if(loadUsers == -1){
		puts("Erro ao carregar utilizadores");
	} else {
		char cmdTeste[TAM];
		do {
			printf("Deseja testar que funcionalidades?\n(comandos/promotores/utilizadores/itens/exit)\n");
			scanf("%s", cmdTeste);
			if (strcmp(cmdTeste, "comandos") == 0) {
				adminInput();
			} else if (strcmp(cmdTeste, "promotores") == 0) {
				lancaPromotores("black_friday");
			} else if (strcmp(cmdTeste, "utilizadores") == 0) {
				checkUsers();
			} else if (strcmp(cmdTeste, "itens") == 0) {
				showItens(listaItens);
			} else if (strcmp(cmdTeste, "exit") == 0) {
				strcpy(cmdTeste, "");
			} else {
				printf("Comando '%s' desconhecido\n", cmdTeste);
			}
		} while(strlen(cmdTeste) > 1);
	}
	int x = saveUsersFile(USER_PATH);
	
	if (x == -1)
		printf("Erro ao gravar utilizadores");
}