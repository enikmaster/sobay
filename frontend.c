#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
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
    strcpy(u.username, argv[1]);
    strcpy(u.pwd, argv[2]);
    strcpy(u.fifoname, fifoname);
    
    printf("COM: %d | USERNAME: %s | PDW: %s | FIFO: %s \n", u.comando, u.username, u.pwd, u.fifoname);
    write(sendFD, &u, sizeof(u));
    close(sendFD);

    int verificaLogin;  // 1 -> Se a operação for autorizada pelo backend // 0 -> se for rejeitado

    printf("rcv:");

    

    

    while (read(rcvFD, &verificaLogin, sizeof(int)) < 1)
    {
    
    }
    
    printf("Recebeu %d", verificaLogin);

    if(argc < 3 || verificaLogin == 0) {
        printf("Dados incorretos.");
        unlink(fifoname);
        return 1;
    }

    int v = 0;

    
    printf("Bem vindo, %s!\n", argv[1]);

    do {
        v = userInput(pid);
    } while (v == 0);

    unlink(fifoname);
    return 0;

}