#include "token.h"
#include "utils.h"
#include<string.h>
/*
    lexeme_n: lexeme size
    literal_n: literal size
*/

Token * newtoken(token_t type, char* lexeme, int lexeme_n, Object * literal, int line)
{
    Token * token = (Token*)malloc(sizeof(Token));
    if (token != NULL) 
    { 
        token->type = type;
        token->lexeme = allocstr(lexeme_n);
        token->literal = literal;
        token->line = line;
        return token;
    }
    exit(EX_MEMALLOC); 
}

char * tostr_token(Token * tk) {
    char * buffer = allocstr(200);
    strcat(buffer, tk->type);
    strcat(buffer, " ");
    strcat(buffer, tk->lexeme);
    strcat(buffer, " ");
    strcat(buffer, tk->literal->data);
    return buffer;
}