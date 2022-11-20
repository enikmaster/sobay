#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

#define TAM 256

int adminInput();
void cmdCheck(const int argNum, const char* cmd, const char* arg);
void lancaPromotores(char* fileName);
void stopPromotor(int x,siginfo_t* i, void* v);