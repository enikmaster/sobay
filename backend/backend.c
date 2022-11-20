#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
// #include "../constantes.h"
#include "backend.h"
#include "backendFunctions.c"

void main(int argc, char** argv) {

	struct item* listaItens = NULL;
	listaItens =  recebeItems(listaItens);
	showItens(listaItens);

	// verificação de backend já em execução
	printf("Bem-vindo administrador\n");
	//adminInput();
}