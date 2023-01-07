#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>
#include "backend.h"
#include "users_lib.h"

void main(int argc, char** argv) {


	// Criação do name pipe que recebe os dados do frontend
	if(mkfifo(BACKEND, 0777) == -1) {
		if(errno == EEXIST) {
			printf("Já existe um backend a executar.\n");
			return;
		}
	} else {
			int loadUsers = loadUsersFile(USER_PATH);

			
			struct item* listaItens = NULL;
			listaItens =  recebeItems(listaItens);
			// showItens(listaItens);

			// verificação de backend já em execução
			puts("Bem-vindo administrador");

			pthread_t rcv;
			if (pthread_create(&rcv, NULL, &receive, NULL) != 0)
			{
				printf("Erro com a thread que recebe data do frontend");
				return 1;
			}

			/*pthread_t input;
			if (pthread_create(&input, NULL, &TadminInput, listaItens) != 0)
			{
				printf("Erro com a Thread do admin input");
				return 1;
			}*/
			

			
			if(loadUsers == -1){
				puts("Erro ao carregar utilizadores");
			} 
			int x = saveUsersFile(USER_PATH);
		
			if (x == -1)
				printf("Erro ao gravar utilizadores");

			while (1)
			{
				/* code */
			}

			pthread_join(rcv, NULL);
			
			

			unlink(BACKEND);
		}

}