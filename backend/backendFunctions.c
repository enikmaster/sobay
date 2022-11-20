#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

//#include "../constantes.h"
#include "backend.h"

int pidfilho;

int adminInput() {
	char str[TAM];
	do {
		printf("O que vamos testar?\n");
		fgets(str, TAM, stdin);
		int cnt = 0;
		for (int i = 0; i < strlen(str); ++i) {
			if (str[i] == ' ')
				++cnt;
		}
		if (cnt <= 0 && strlen(str)-1 <= 0) {
			printf("Nada foi escrito\n");
		} else if (cnt >= 2) {
			printf("Demasiados argumentos\n");
		} else {
			char cmd[TAM], arg[TAM];
			int argNum = sscanf(str, "%s %s", cmd, arg);
			cmdCheck(argNum, cmd, arg);
		}
	} while(strlen(str) > 1);
	return 0;
}

void cmdCheck(const int argNum, const char* cmd, const char* arg) {
	if(strcmp(cmd, "users") == 0) // users - listar todos os clientes a usar a plataforma
		(argNum-1 != 0) ? printf("Este comando nao recebe argumentos...\n") : printf("Comando %s validado.\n", cmd);
	else if(strcmp(cmd, "list") == 0) // list - listar intes à venda(<id> <nome-item> <categoria> <preço-atual> <compre-ja> <seller> <higher-bider ou '-' >)
		(argNum-1 != 0) ? printf("Este comando nao recebe argumentos...\n") : printf("Comando %s validado.\n", cmd);
	else if(strcmp(cmd, "kick") == 0) // kick <username> - banir um cliente atualmente logado, como se o cliente tivesse feito logout
		(argNum-1 != 1) ? printf("Este comando precisa de 1 argumento...\n") : printf("Comando %s validado.\n", cmd);
	else if(strcmp(cmd, "prom") == 0) // prom - listar os promotores atualmente ativos
		(argNum-1 != 0) ? printf("Este comando nao recebe argumentos...\n") : printf("Comando %s validado.\n", cmd);
	else if(strcmp(cmd, "reprom") == 0) // reprom - atualizar os promotores, lê o ficheiro dos promotores novamente, encerrando os que deixaram de estar no ficheiro, carrega os novos, mantém inalterados os restantes
		(argNum-1 != 0) ? printf("Este comando nao recebe argumentos...\n") : printf("Comando %s validado.\n", cmd);
	else if(strcmp(cmd, "cancel") == 0) // cancel <nome-do-executavel-do-promotor> - cancela um promotor, deixa de estar em execução
		(argNum-1 != 1) ? printf("Este comando precisa de 1 argumentos...\n") : printf("Comando %s validado.\n", cmd);
	else if(strcmp(cmd, "close") == 0) // close - encerra a plataforma, avisando todos
		(argNum-1 != 0) ? printf("Este comando nao recebe argumentos...\n") : printf("Comando %s validado.\n", cmd);
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

	char path[TAM] = "../promotores_prof/";
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