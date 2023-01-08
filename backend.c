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
			dados.itens = recebeItems(dados.itens);
			pthread_mutex_init(&(dados.mutex), NULL);

			// verificação de backend já em execução
			puts("Bem-vindo administrador");

			pthread_t rcv;
			if (pthread_create(&rcv, NULL, &receive, &dados) != 0)
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
			{
				sleep(2);
				//printf("Utilizadores online:\n");
				/*if (dados.online == NULL)
				{
					printf("Sem utilizadores online.\n");
				} else {
					utilizadorLogin* aux = malloc(sizeof(utilizadorLogin));
					aux = dados.online;
					while (aux != NULL)
					{
						printf("Nome: %s\n FIFO: %s", aux->username, aux->fifoname);
						aux = aux->seguinte;
					}
					
					
				}*/

				/*if (dados.itens == NULL)
				{
					printf("Não há itens à venda.");
				} else {
					struct item* aux = dados.itens;

					while (aux != NULL)
					{
						printf("Nome: %s | Preço: %d\n", aux->titulo, aux->compreJa);
						aux = aux->next;
					}
					
				}*/
				
				
				
			}

			pthread_join(rcv, NULL);
			
			

			unlink(BACKEND);
		}

}