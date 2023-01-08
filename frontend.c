#include "frontend.h"
//#include "frontendFunctions.c"



int main (int argc, char **argv) {

    if (argc < 3)
    {
        printf("Insira um utilizador e password\n");
        return;
    }
    

    int pid = getpid();
    char pidAsString[10];
    sprintf(pidAsString, "%d", pid);
    char fifoname[TAM] = "FRONT";
    strcat(fifoname, pidAsString);

    if(mkfifo(fifoname, 0777) == -1) {
        perror("");
        return 1;
    }

    
    
    int sendFD = open(BACKEND, O_RDWR);
    int rcvFD = open(fifoname, O_RDWR);
    

    utilizadorLogin u;
    u.comando = login;
    u.seguinte = NULL;
    strcpy(u.username, argv[1]);
    strcpy(u.pwd, argv[2]);
    strcpy(u.fifoname, fifoname);
    
    write(sendFD, &u, sizeof(u));
    close(sendFD);

    int res;  // 1 -> Se a operação for autorizada pelo backend // 0 -> se for rejeitado

    while (read(rcvFD, &res, sizeof(int)) < 1) {}
    

    if(argc < 3 || res == 0) {
        printf("Dados incorretos.");
        unlink(fifoname);
        return 1;
    }

   

    printf("Bem vindo, %s!\n", argv[1]);

    TDADOS_FRONT dados;
    strcpy(dados.fifoname, fifoname);
    strcpy(dados.username, u.username);

    pthread_t rcv;
    if (pthread_create(&rcv, NULL, &receive, &dados) != 0)
    {
        printf("Erro ao iniciar thread\n");
        return 0;
    }
    
    pthread_t input;
    if (pthread_create(&input, NULL, &cmdInput, &dados) != 0)
    {           
        printf("Erro ao iniciar thread\n");
        return 0;
    }
    
    pthread_join(input, NULL);
    

    

    unlink(fifoname);
    return 0;

}