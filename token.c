#include "token.h"
#include "utils.h"
#include<string.h>
/*
    lexeme_n: lexeme size
    literal_n: literal size
*/

int token_count;

int tokenscount(void) { return token_count; }

Token * newtoken(token_t type, char* lexeme, int lexeme_n, Object * literal, int line)
{
    Token * token = (Token*)malloc(sizeof(Token));
    if (token != NULL) 
    { 
        token->type = type;
        token->lexeme = allocstr(lexeme_n);
        token->literal = literal;
        token->line = line;
        token->next = NULL;
        return token;
    }

    exit(EX_MEMALLOC); 
}

char * tostr_token(Token * tk) {
    char * buffer = allocstr(200);
    // strcat(buffer, tk->type); // error: incompatible type for argument 2 of ‘strcat’
    strcat(buffer, " ");
    strcat(buffer, tk->lexeme);
    strcat(buffer, " ");
    strcat(buffer, tk->literal->data);
    return buffer;
}

TokensV * init_tokens_array(void)
{
    TokensV * v = (TokensV*)malloc(BASE_TOKENS_QTD * sizeof(TokensV));
    if (v != NULL)
    {
        for(int i = 0; i < BASE_TOKENS_QTD; i++)
            v->list[i] = NULL;
        return v;
    }
    exit(EX_MEMALLOC);
}

Token * pushf(Token * newtk, Token * stack)
{
    struct token * aux = NULL;
    struct token * p = stack;
    if (newtk != NULL)
    {
        if (p == NULL)
            p = newtk;
        else
        {
            aux = p;
            while(aux->next) 
            { 
                aux = aux->next; 
            }
            aux->next = newtk;
        }
        stack = p;
        token_count++;
    }
    return stack;
}

void print_tokensv(TokensV * v)
{
    for(int i=0; i < BASE_TOKENS_QTD; i++)
    {
        for(struct token* p = v->list[i]; p != NULL; p = p->next)
        {
            printf("Token [%d]: line: %d, lexeme: %s\n", i, p->line, p->lexeme);
        }
    }
}

void print_token(Token * stack)
{
	Token* p;
    int i = 0;
	for (p = stack; p != NULL; p = p->next)
	{
        printf("Token [%d]: line: %d, lexeme: %s\n", i, p->line, p->lexeme);
        i++;
	}
}