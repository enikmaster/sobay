#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "frontend.h"

int userInput(int pid) {

    char buffer[TAM];
    char str[6][TAM];

    printf("-> ");
    fgets(buffer, sizeof(buffer), stdin);

    int quantArg = sscanf(buffer ,"%s %s %s %s %s %s", str[0], str[1], str[2], str[3], str[4], str[5]);

    if(strcmp(str[0], "exit") == 0) {
        if(quantArg == 1)
            return userExit(pid);
        else
            printf("Número de argumentos errados!\n");
    } else if (strcmp(str[0], "sell") == 0) {
        if (quantArg == 6)
            userSell(pid, str[1], str[2], atoi(str[3]), atoi(str[4]), atoi(str[5]));
        else
            printf("Número de argumentos errados!\n");
    } else if (strcmp(str[0], "list") == 0) {
        if (quantArg == 1)
            userList(pid);
        else
            printf("Número de argumentos errados!\n");
    } else if (strcmp(str[0], "licat") == 0) {
        if (quantArg == 2)
            userLicat(pid, str[1]);
        else
            printf("Número de argumentos errados!\n");
    } else if (strcmp(str[0], "lisel") == 0) {
        if (quantArg == 2)
            userLiSel(pid, str[1]);
        else
            printf("Número de argumentos errados!\n");
    } else if (strcmp(str[0], "lival") == 0) {
        if (quantArg == 2)
            userLiVal(pid, atoi(str[1]));
        else
            printf("Número de argumentos errados!\n");
    } else if (strcmp(str[0], "litime") == 0) {
        if (quantArg == 2)
            userLiTime(pid, atoi(str[1]));
        else
            printf("Número de argumentos errados!\n");
    } else if (strcmp(str[0], "time") == 0) {
        if (quantArg == 1)
            userTime(pid);
        else
            printf("Número de argumentos errados!\n");
    } else if (strcmp(str[0], "buy") == 0) {
        if (quantArg == 3)
            userBuy(pid, atoi(str[1]), atoi(str[2]));
        else
            printf("Número de argumentos errados!\n");
    } else if (strcmp(str[0], "cash") == 0) {
        if (quantArg == 1)
            userCash(pid);
        else
            printf("Número de argumentos errados!\n");
    } else if (strcmp(str[0], "add") == 0) {
        if (quantArg == 2)
            userAdd(pid, atoi(str[1]));
        else
            printf("Número de argumentos errados!\n");
    } else {
        printf("Comando inválido!\n");
    }

    return 0;
}

int userExit(int pid) {
    printf("Utilizador com pid: %d pediu para sair.\n", pid);
    return 1;
}

void userSell(int pid, char* nItem, char* categoria, int precoBase, int precoCompreJa, int tempo ) {
    printf("O utilizador %d colocou à venda o item %s da categoria %s com o preço Base %d, o preco compre já %d durante %d segundos.\n", pid, nItem, categoria, precoBase, precoCompreJa, tempo);
}

void userList(int pid) {
    printf("O utilizador %d quer listar todos os itens.\n", pid);
}

void userLicat(int pid, char* categoria) {
    printf("O utilizador %d quer listar todos os itens da categoria %s \n", pid, categoria);
}

void userLiSel(int pid, char* username) {
    printf("O utilizador %d quer listar todos os itens do utilizador %s \n", pid, username);
}

void userLiVal(int pid, int precoMax) {
    printf("O utilizador %d quer listar todos os itens com preço máximo até %d\n", pid, precoMax);
}

void userLiTime(int pid, int tempo) {
    printf("O utilizador %d quer listar todos os produtos com prato até %d segundos \n", pid, tempo);
}

void userTime(int pid) {
    printf("O utilizador %d quer saber a hora atual.\n", pid);
}

void userBuy(int pid, int itemID, int valor) {
    printf("O utilizador %d quer comprar o item %d, por %d\n", pid, itemID, valor);
}

void userCash(int pid) {
    printf("O utilizador %d quer saber o seu saldo\n", pid);
}

void userAdd(int pid, int valor) {
    printf("O utilizador %d quer adicinoar %d ao seu saldo\n", pid, valor);
}
