#pragma once
#include "utils.h"

#define TEMP_MAX_VTOKENS 500 /* max vtokens (temporario) */
#define BASE_TOKENS_QTD 5000

typedef enum {
    // Single-character tokens
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE, // Chave esquerda
    RIGHT_BRACE,
    COMMA,
    DOT, 
    MINUS,
    PLUS, 
    SEMICOLON,
    SLASH,
    STAR,

    // One or two character tokens.
    BANG, // ! 
    BANG_EQUAL, // !=
    GREATER, 
    GREATER_EQUAL,
    LESS,
    LESS_EQUAL,
    EQUAL_EQUAL,
    EQUAL,
    
    // Literals
    IDENTIFIER, STRING, NUMBER,

    // Keywords
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,
    ENDOFFILE,

    // defaults
    NONE
}token_t; 

struct token {
    token_t type;
    char* lexeme;
    Object * literal;
    int line;
    struct token * next;
};
typedef struct token Token;

struct tokens_v {
    struct token * list[BASE_TOKENS_QTD];
};

typedef struct tokens_v TokensV;

Token * newtoken(token_t type, char* lexeme, int lexeme_n, Object *literal, int line);
char * tostr_token(Token * tk);
TokensV * init_tokens_array(void);
Token * pushf(Token * newtk, Token * stack);
void print_tokensv(TokensV * v);
void print_token(Token * stack);
int tokenscount(void);