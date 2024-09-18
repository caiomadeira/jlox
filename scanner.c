#include "scanner.h"
#include "token.h"

Scanner * newscanner(char * source, int source_n)
{
    Scanner *scanner = (Scanner*)malloc(sizeof(Scanner));
    if (scanner != NULL)
    {
        scanner->source = allocstr(source_n);
        scanner->vtokens = allocvtokens(TEMP_MAX_VTOKENS);
        scanner->start = SCANNER_START;
        scanner->current = 0;
        scanner->line = 1;
        return scanner;
    }
    exit(EX_MEMALLOC);
}

int isatend(int current, int source_n) 
{ 
    if (current >= source_n)
        return U_TRUE;
    else
        return U_FALSE;
}

void printtokensv(Token** vtoken, int tokens_n)
{
    printf("Print tokens:\n");
    for(int i = 0; i < tokens_n; i++)
        printf("[%d] - lexeme(%s) - line(%d)\n", i, vtoken[i]->lexeme, vtoken[i]->line);
}

Token ** scantokens(Scanner * s, int source_n, int tokens_n)
{
    //while(isatend(s->current, source_n) != 1)
    while(s->current >= source_n)
    {
        s->start = s->current;
        scantokens(s, source_n, tokens_n);
    };

    s->vtokens[tokens_n] = newtoken(ENDOFFILE, NULL, 0, NULL, s->line);
    return s->vtokens;
}

Token ** allocvtokens(int tokens_n)
{
    Token ** v = (Token**)malloc(tokens_n * sizeof(Token*));
    if (v != NULL)
    {
        for(int i = 0; i < tokens_n; i++)
        {
            v[i] = (Token*)malloc(sizeof(Token));
            if (v[i] != NULL)
            {
                v[i]->lexeme = NULL; 
                v[i]->line = 1;
                v[i]->type = NONE;
            } else { exit(EX_MEMALLOC); }
        }
    } else { exit(EX_MEMALLOC); }
    return v;
}

void scantoken() 
{
    char c = nextchar();
    switch (c)
    {
        case '(': addtoken(LEFT_PAREN); break;
        case ')': addtoken(RIGHT_PAREN); break;
        case '{': addtoken(LEFT_BRACE); break;
        case '}': addtoken(RIGHT_BRACE); break;
        case ',': addtoken(COMMA); break;
        case '.': addtoken(DOT); break;
        case '-': addtoken(MINUS); break;
        case '+': addtoken(PLUS); break;
        case ';': addtoken(SEMICOLON); break;
        case '*': addtoken(STAR); break;
    }
}

char nextchar(char * source)
{
    
}

void addtoken(token_t type, Object * literal)
{
    
}