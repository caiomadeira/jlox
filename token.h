#pragma once
#include "utils.h"

#define TEMP_MAX_VTOKENS 500 /* max vtokens (temporario) */

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
    
    // Literals
    IDENTIFIER, STRING, NUMBER,

    // Keywords
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,
    ENDOFFILE,

    // defaults
    NONE
}token_t; 

typedef struct {
    token_t type;
    char* lexeme;
    Object * literal;
    int line;
} Token;

Token * newtoken(token_t type, char* lexeme, int lexeme_n, Object *literal, int line);
char * tostr_token(Token * tk);