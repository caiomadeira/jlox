#include "scanner.h"

#define TEMP_MAX_VTOKENS 5000 /* max vtokens (temporario) */

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

Token ** scantokens(Scanner * s, int source_n, int tokens_n)
{
    while(isatend(s->current, source_n) != 1)
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
                v[i]->line = NULL;
                v[i]->type = NULL;
                return v;
            } else { exit(EX_MEMALLOC); }
        }
    } else { exit(EX_MEMALLOC); }
}