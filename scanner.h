#pragma once
#include "token.h"

#define SCANNER_START 0
#define SCANNER_CURRENT = 0;
#define SCANNER_LINE = 1

/*
Talvez vtokens seja melhor listas encadeadas, pois não sabemos o quanto
essa estrutura pode crescer;
*/

typedef struct {
    char * source;
    struct token * linkedtokens;
    int start;
    int current;
    int line;
} Scanner;

int isatend(int current, int source_n);
Scanner * newscanner(char * source, int source_n);
Token * scantokens(Scanner * s, int source_n, int tokens_n);
//Token * allocvtokens(int tokens_n);
void printtokensv(Token** vtoken, int tokens_n);
char advance(Scanner *s, char *source);
void addtoken(Scanner *s, char *source, token_t type);
void addtokenwliteral(Scanner *s, char *source, token_t type, Object *literal);
int match(Scanner * s, int source_n, char expected);