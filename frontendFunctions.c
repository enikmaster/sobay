#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "frontend.h"

int userInput(char* username, int pid) {

    char buffer[TAM];
    char str[6][TAM];

    printf("-----------------------------\n");
    printf("-> ");
    fgets(buffer, sizeof(buffer), stdin);

    int quantArg = sscanf(buffer ,"%s %s %s %s %s %s", str[0], str[1], str[2], str[3], str[4], str[5]);

    if(strcmp(str[0], "exit") == 0) {
        if(quantArg == 1)
            return userExit(username);
        else
            printf("Número de argumentos errados!\n");
    } else if (strcmp(str[0], "sell") == 0) {
        if (quantArg == 6)
            userSell(username, str[1], str[2], atoi(str[3]), atoi(str[4]), atoi(str[5]));
        else
            printf("Número de argumentos errados!\n");
    } else if (strcmp(str[0], "list") == 0) {
        if (quantArg == 1)
            userList(username);
        else
            printf("Número de argumentos errados!\n");
    } else if (strcmp(str[0], "licat") == 0) {
        if (quantArg == 2)
            userLicat(username, str[1]);
        else
            printf("Número de argumentos errados!\n");
    } else if (strcmp(str[0], "lisel") == 0) {
        if (quantArg == 2)
            userLiSel(username, str[1]);
        else
            printf("Número de argumentos errados!\n");
    } else if (strcmp(str[0], "lival") == 0) {
        if (quantArg == 2)
            userLiVal(username, atoi(str[1]));
        else
            printf("Número de argumentos errados!\n");
    } else if (strcmp(str[0], "litime") == 0) {
        if (quantArg == 2)
            userLiTime(username, atoi(str[1]));
        else
            printf("Número de argumentos errados!\n");
    } else if (strcmp(str[0], "time") == 0) {
        if (quantArg == 1)
            userTime(username);
        else
            printf("Número de argumentos errados!\n");
    } else if (strcmp(str[0], "buy") == 0) {
        if (quantArg == 3)
            userBuy(username, atoi(str[1]), atoi(str[2]));
        else
            printf("Número de argumentos errados!\n");
    } else if (strcmp(str[0], "cash") == 0) {
        if (quantArg == 1)
            userCash(username);
        else
            printf("Número de argumentos errados!\n");
    } else if (strcmp(str[0], "add") == 0) {
        if (quantArg == 2)
            userAdd(username, atoi(str[1]));
        else
            printf("Número de argumentos errados!\n");
    } else {
        printf("Comando inválido!\n");
    }

    return 0;
}

int userExit(char *user) {
    int sendFD = open(BACKEND, O_RDWR);

    utilizadorExit e;
    e.comando = exitP;
    strcpy(e.username, user);

    write(sendFD, &e, sizeof(e));
    close(sendFD);

    return 1;
}

void userSell(char* user, char* nItem, char* categoria, int precoBase, int precoCompreJa, int tempo ) {
    int sendFD = open(BACKEND, O_RDWR);

    utilizadorSell s;

    s.comando = sell;
    strcpy(s.categoria, categoria);
    strcpy(s.titulo, nItem);
    strcpy(s.seller, user);
    strcpy(s.bidder, "-");
    s.next = NULL;
    s.valorAtual = precoBase;
    s.compreJa = precoCompreJa;
    s.tempo = tempo;
    s.id = -1;

    write(sendFD, &s, sizeof(s));
    close(sendFD);
}

void userList(char* user) {

    int sendFD = open(BACKEND, O_RDWR);

    utilizadorList l;

    l.comando = list;
    strcpy(l.username, user);

    write(sendFD, &l, sizeof(l));
    close(sendFD);    
}

void userLicat(char* user, char* categoria) {
    int sendFD = open(BACKEND, O_RDWR);

    utilizadorLi_ l;

    l.comando = licat;
    strcpy(l.username, user);
    strcpy(l.str, categoria);

    write(sendFD, &l, sizeof(l));
    close(sendFD);
}

void userLiSel(char* user, char* username) {
    int sendFD = open(BACKEND, O_RDWR);

    utilizadorLi_ l;

    l.comando = lisel;
    strcpy(l.username, user);
    strcpy(l.str, username);

    write(sendFD, &l, sizeof(l));
    close(sendFD);
}

void userLiVal(char* user, int precoMax) {
    int sendFD = open(BACKEND, O_RDWR);

    utilizadorLi_ l;

    l.comando = lival;
    strcpy(l.username, user);
    l.i = precoMax;
    
    write(sendFD, &l, sizeof(l));
    close(sendFD);
}

void userLiTime(char* user, int tempo) {
    int sendFD = open(BACKEND, O_RDWR);

    utilizadorLi_ l;

    l.comando = litime;
    strcpy(l.username, user);
    l.i = tempo;
    
    write(sendFD, &l, sizeof(l));
    close(sendFD);
}

void userTime(char* user) {
    int sendFD = open(BACKEND, O_RDWR);

    utilizadorTime t;

    t.comando = timeP;
    strcpy(t.username, user);

    write(sendFD, &t, sizeof(t));
    close(sendFD);
}

void userBuy(char* user, int itemID, int valor) {
    int sendFD = open(BACKEND, O_RDWR);

    utilizadorBuy b;

    b.comando = buy;
    strcpy(b.username, user);
    b.id = itemID;
    b.valor = valor;

    write(sendFD, &b, sizeof(b));
    close(sendFD);
}

void userCash(char* user) {
    int sendFD = open(BACKEND, O_RDWR);

    utilizadorBuy b;

    b.comando = cash;
    strcpy(b.username, user);

    write(sendFD, &b, sizeof(b));
    close(sendFD);
}

void userAdd(char* user, int valor) {
    int sendFD = open(BACKEND, O_RDWR);

    utilizadorAdd a;

    a.comando = add;
    strcpy(a.username, user);
    a.valor = valor;

    write(sendFD, &a, sizeof(a));
    close(sendFD);
}


// THREADS

void* receive(void* dados) {

    TDADOS_FRONT* pdados = (TDADOS_FRONT *) dados;

    int rcvFD = open(pdados->fifoname, O_RDONLY);
    responseToFrontend res;


    while (1)
    {
        read(rcvFD, &res, sizeof(responseToFrontend));
        

        switch (res.cmd)
        {
        case sell:
            if(res.i == 1)
                printf("O seu item foi listado com sucesso!\n");
            else
                printf("Houve um erro ao listar o seu item por favor tente de novo.\n");
            break;
        case list:
            for (int i = 0; i < res.quantItens; i++)
            {
                printf("--------- ID: %d ---------\n", res.itens[i].id);
                printf("Titulo: %s\n", res.itens[i].titulo);
                printf("Categoria: %s\n", res.itens[i].categoria);
                printf("Licitação Atual: %d\n", res.itens[i].precoBase);
                printf("Compre Já: %d\n", res.itens[i].precoCompreJa);
                printf("Tempo Restante: %d\n", res.itens[i].duracao);
            }
            
            break;
        case licat:
            for (int i = 0; i < res.quantItens; i++)
            {
                printf("\n--------- ID: %d ---------\n", res.itens[i].id);
                printf("Titulo: %s\n", res.itens[i].titulo);
                printf("Categoria: %s\n", res.itens[i].categoria);
                printf("Licitação Atual: %d\n", res.itens[i].precoBase);
                printf("Compre Já: %d\n", res.itens[i].precoCompreJa);
                printf("Tempo Restante: %d\n", res.itens[i].duracao);
            }
            break;
        case lisel:
            for (int i = 0; i < res.quantItens; i++)
            {
                printf("\n--------- ID: %d ---------\n", res.itens[i].id);
                printf("Titulo: %s\n", res.itens[i].titulo);
                printf("Categoria: %s\n", res.itens[i].categoria);
                printf("Licitação Atual: %d\n", res.itens[i].precoBase);
                printf("Compre Já: %d\n", res.itens[i].precoCompreJa);
                printf("Tempo Restante: %d\n", res.itens[i].duracao);
            }
        break;
        case lival:
            for (int i = 0; i < res.quantItens; i++)
            {
                printf("\n--------- ID: %d ---------\n", res.itens[i].id);
                printf("Titulo: %s\n", res.itens[i].titulo);
                printf("Categoria: %s\n", res.itens[i].categoria);
                printf("Licitação Atual: %d\n", res.itens[i].precoBase);
                printf("Compre Já: %d\n", res.itens[i].precoCompreJa);
                printf("Tempo Restante: %d\n", res.itens[i].duracao);
            }
        break;
        case litime:
            for (int i = 0; i < res.quantItens; i++)
            {
                printf("\n--------- ID: %d ---------\n", res.itens[i].id);
                printf("Titulo: %s\n", res.itens[i].titulo);
                printf("Categoria: %s\n", res.itens[i].categoria);
                printf("Licitação Atual: %d\n", res.itens[i].precoBase);
                printf("Compre Já: %d\n", res.itens[i].precoCompreJa);
                printf("Tempo Restante: %d\n", res.itens[i].duracao);
            }
        break;
        case buy:
            /*
                0: Não tem dinhero
                1: comprou logo
                2: passou a bidder
                3: não encontrado
            */
           switch (res.i)
           {
           case 0:
            printf("Não tem dinheiro para comprar este artigo.\n");
            break;
           case 1:
            printf("PARABÉNS! Comprou o artigo\n");
            break;
            case 2:
            printf("É algora o BIDDER mais alto deste artigo.\n");
            break;
            case 3:
            printf("Esse produto não existe. Tente de novo.\n");
            break;
            case 4:
            printf("Valor licitado abaixo do valor atual.\n");
            break;
           default:
            break;
           }
        break;
        case cash:
            printf("Tem neste momento: %d€\n", res.i);
        break;
        case add:
            printf("Saldo atualizado! Tem agora %d€\n", res.i);
        break;
        case timeP:
            printf("Hora atual: %d\n", res.i);
        break;
        default:
            break;
        }
    }
    
}

void* cmdInput(void* dados) {

    TDADOS_FRONT* pdados = (TDADOS_FRONT *) dados;

     int v = 0;

    do {
        v = userInput(pdados->username, getpid());
        sleep(1);
    } while (v == 0);
}