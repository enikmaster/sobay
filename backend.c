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

		
			TDADOS dados;
			dados.online = NULL;
			dados.itens = NULL;
			dados.tempo = 0;
			dados.itens = recebeItems(dados.itens);
			pthread_mutex_init(&(dados.mutex), NULL);

			puts("Bem-vindo administrador");

			pthread_t rcv;
			if (pthread_create(&rcv, NULL, &receive, &dados) != 0)
			{
				printf("Erro com a thread que recebe data do frontend");
				return 1;
			}

			pthread_t tempo;
			if (pthread_create(&tempo, NULL, &segundo, &dados) != 0)
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


			int a;
			while (1)
			{}

			pthread_join(rcv, NULL);
			
			

			unlink(BACKEND);
		}

}