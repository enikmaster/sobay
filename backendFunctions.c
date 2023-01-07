#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include<fcntl.h>
#include<errno.h>

//#include "../constantes.h"
#include "backend.h"
#include "users_lib.h"

int pidfilho;

int adminInput() {

	char str[TAM];
	do {
		printf("O que pretende testar?\n");
		setbuf(stdin, NULL);
		//fgets(str, TAM, stdin);
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
			strcpy(cmd, tolower(cmd)); 
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

void stopPromotor(int x,siginfo_t* i, void* v){
    if(kill(pidfilho, SIGUSR1) == -1 ){
        printf("Não foi possivel enviar o sinal!");
        return;
    }
	pidfilho = -1;
}

void lancaPromotores(char* fileName) {

    int p[2];
    char res[TAM];

	char path[TAM] = "/promotores_prof/";
	strcat(path, fileName);

	if (pipe(p) == -1) {
        printf("Erro ao criar o pipe\n");
        return;
    };

	int i;
    int f = fork();
	pidfilho = f;

    if (f == 0) { // filho

        close(p[0]); // fecha o descritor de leitura
        close(1); // fecha o stdout
        dup(p[1]); // duplica o descritor de escrita para a pos do stdout
        close(p[1]); // fecha do descritor de escrita do pipe criado

		execl(path, "promotor", NULL);
		printf("erro\n");
		exit(1);
        
    } else if(f > 1) {
		
		close(p[1]);

		struct sigaction sac = {0};
        sac.sa_sigaction = stopPromotor;
        if(sigaction(SIGINT, &sac, NULL)==-1){
            printf("Erro no sigaction\n");
		}

		while (pidfilho != -1)
		{
			read(p[0], &res, TAM);
        	printf("%s", res);
		}
		//waitpid(f, &i, 0);
		close(p[0]);
    }
}

struct item* recebeItems(struct item* itemptr) {


	char buf[TAM] = "";
	char c[1];
	int fd;
	

	//int id, valor, compreja, tempo;
	char titulo[TAM], categoria[TAM], seller[TAM], bidder[TAM], id[5], valor[5], compreja[5], tempo[5];


	if ((fd = open("conteudos/FITEMS.txt", O_RDONLY)) == -1) {
		printf("Erro ao abrir o ficheiro");
	}


	while (read(fd, c, sizeof(char)) != 0)
	{
		item* itemAux = malloc(sizeof(item));
		item* itemAuxItr = itemptr;

		if (c[0] == '\n')
		{
			sscanf(buf, "%s %s %s %s %s %s %s %s", id, titulo, categoria, valor, compreja, tempo, seller, bidder);
			
			// INT
			itemAux->id = atoi(id);
			itemAux->valorAtual = atoi(valor);
			itemAux->compreJa = atoi(compreja);
			itemAux->tempo = atoi(tempo);
			
			// STRINGS
			strcpy(itemAux->titulo, titulo);
			strcpy(itemAux->categoria, categoria);
			strcpy(itemAux->seller, seller);
			strcpy(itemAux->bidder, bidder);

			itemAux->next = NULL;

			if(itemptr == NULL) {
				itemptr = itemAux;
			} else {
				while (itemAuxItr->next != NULL)
				{
					itemAuxItr = itemAuxItr->next;
				}
				itemAuxItr->next = itemAux;
			}

			strcpy(buf, "");
		} else {
			strncat(buf, c, 1);
		}
		
		
	}
	

	close(fd);

	return itemptr;
}

void showItens(struct item* itemptr) {
	if (itemptr == NULL)
	{
		printf("Não existem items à venda");
		return;
	}


	item* aux = itemptr;

	while (aux != NULL)
	{
		printf("ID: %d | Titulo: %s | Categoria: %s | Valor Atual: %d | Compre já: %d | Tempo Restante: %d | Seller: %s | Bidder: %s\n", aux->id, aux->titulo, aux->categoria, aux->valorAtual, aux->compreJa, aux->tempo, aux->seller, aux->bidder);
		aux = aux->next;
	}
	
}

void addItem(item* i, item a) {

	item* aux = malloc(sizeof(item));

	strcpy(aux->bidder, a.bidder);
	strcpy(aux->categoria, a.categoria);
	strcpy(aux->seller, a.seller);
	strcpy(aux->titulo, a.titulo);
	aux->valorAtual = a.valorAtual;
	aux->compreJa = a.valorAtual;
	aux->next = NULL;
	aux->tempo = a.tempo;

	if (i == NULL)
	{
		aux->id = 1;
		i = aux;
		return;
	} else {
		item* aux_itr = i;

		while (aux_itr->next != NULL)
		{
			aux_itr = aux_itr->next;
		}
		aux->id = aux_itr->id + 1;
		aux_itr->next = aux;
		return;
	}
	
}


/* THREADS */

void *receive(void  *dados)
{
	int rcvFD = open(BACKEND, O_RDWR);

	TDADOS *pdados = (TDADOS *) dados;

	comando com;
	utilizadorLogin u;
	item s;
	int res;

	while (1)
	{
		read(rcvFD, &com, sizeof(comando));
		
		switch (com)
		{

		case login:

			read(rcvFD, &u, sizeof(u));
			res = isUserValid(u.username, u.pwd);
			int sndFD = open(u.fifoname, O_RDWR);

			if (res == -1)
			{
				printf("Houve um erro ao verificar os utilizadores");
			}
			else if (res == 0)
			{
				printf("Dados inválidos.");
				int x = write(sndFD, &res, sizeof(int));
				printf("Erro: %d", x);
				close(sndFD);
			}
			else if (res == 1)
			{

				utilizadorLogin* aux = malloc(sizeof(utilizadorLogin));
				strcpy(aux->username, u.username);
				strcpy(aux->pwd, u.pwd);
				strcpy(aux->fifoname, u.fifoname);
				aux->seguinte = NULL;

				pthread_mutex_lock(&(pdados->mutex));
				if (pdados->online == NULL)
				{
					pdados->online = aux;
				} else {
					utilizadorLogin* pdados_aux;
					pdados_aux = pdados->online;

					while (pdados_aux->seguinte != NULL)
					{
						pdados_aux = pdados_aux->seguinte;
					}

					pdados_aux->seguinte = aux;
					
				}
				
				pthread_mutex_unlock(&(pdados->mutex));
				
				write(sndFD, &res, sizeof(int));
				close(sndFD);
			}
			break;
		case sell:

			read(rcvFD, &s, sizeof(s));

			if (s.valorAtual > 0 && s.compreJa > 0 && s.tempo > 0)
			{
				pthread_mutex_lock(&(pdados->mutex));
				addItem(pdados->itens, s);
				pthread_mutex_unlock(&(pdados->mutex));
				res = 1;
			} else
				res = 0;
		
			write(sndFD, &res, sizeof(int));
			break;
		case noCMD:
			break;
		default:
			printf("Default");
			break;
		}
		
		com = 0;
		//sleep(2);
	}
}

void *TadminInput(item* listaItens) {
	char cmdTeste[TAM];
	do
	{
		printf("Deseja testar que funcionalidades?\n(comandos/promotores/utilizadores/itens/exit)\n");
		scanf("%s", cmdTeste);
		if (strcmp(cmdTeste, "comandos") == 0)
		{
				adminInput();
		}
		else if (strcmp(cmdTeste, "promotores") == 0)
		{
				lancaPromotores("black_friday");
		}
		else if (strcmp(cmdTeste, "utilizadores") == 0)
		{
				checkUsers();
		}
		else if (strcmp(cmdTeste, "itens") == 0)
		{
				showItens(listaItens);
		}
		else if (strcmp(cmdTeste, "exit") == 0)
		{
				strcpy(cmdTeste, "");
		}
		else
		{
				printf("Comando '%s' desconhecido\n", cmdTeste);
		}
	} while (strlen(cmdTeste) > 1);
}