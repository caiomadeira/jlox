#include<stdio.h>
#include<stdlib.h>
#include "../../utils.h"
#include "../../scanner.h"
#include "../../token.h"

#define BASE_TOKENS_QTD 5000

int count;

struct tokens_v {
    struct token * list[BASE_TOKENS_QTD];
};

typedef struct tokens_v TokensV;

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
        count++;
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

char * allocstr(int n)
{
    char * buffer = (char *)malloc(n*sizeof(char) + 1);
    if (buffer == NULL) { exit(EX_MEMALLOC); }
    return buffer;
}

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

int main(void)
{
    count = 0;
    //TokensV * stack = init_tokens_array();
    
    Token * stack = NULL;

    Object * literal_test = (Object*)malloc(sizeof(Object));
    if (literal_test != NULL)
    {
        literal_test->data = INT_T;
        literal_test->type = 'c';
        Token * newtk = newtoken(NUMBER, "test", 2, literal_test, 1);
        Token * newtk2 = newtoken(NUMBER, "test", 2, literal_test, 67);
        Token * newtk3 = newtoken(NUMBER, "test", 2, literal_test, 34);

        stack = pushf(newtk, stack);
        stack = pushf(newtk2, stack);
        stack = pushf(newtk3, stack);

        //print_tokensv(stack);
        print_token(stack);
    }

    return 0;
}