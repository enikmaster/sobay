#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../constantes.h"
#include "backend.h"
#include "backendFunctions.c"
#include "users_lib.h"

void main(int argc, char** argv) {

	struct item* listaItens = NULL;
	listaItens =  recebeItems(listaItens);
	showItens(listaItens);

	// verificação de backend já em execução
	puts("Bem-vindo administrador");
	int loadUsers = loadUsersFile(USER_PATH);
	if(loadUsers == -1){
		puts("Erro ao carregar utilizadores");
	} else {
		checkUsers();
	}
	int x = saveUsersFile(USER_PATH);
	
	if (x == -1)
		printf("Erro ao gravar utilizadores");

	
	// adminInput();

	// não esquecer de passar o ponteiro para a estrutura
}