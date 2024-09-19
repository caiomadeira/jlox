#include "scanner.h"
#include "token.h"
#include "utils.h"

Token* stack = NULL;


Scanner *newscanner(char *source, int source_n)
{
    Scanner *scanner = (Scanner *)malloc(sizeof(Scanner));
    if (scanner != NULL)
    {
        scanner->source = allocstr(source_n);
        //scanner->vtokens = allocvtokens(TEMP_MAX_VTOKENS);
        scanner->linkedtokens = NULL;
        scanner->start = SCANNER_START;
        scanner->current = 0;
        scanner->line = 1;
        return scanner;
    }
    exit(EX_MEMALLOC);
}

/*
int isatend(int current, int source_n)
{
    if (current >= source_n)
        return U_TRUE;
    else
        return U_FALSE;
}

is at end 2

int isAtEnd2() {
    return source[current] == '\0';
}

*/

int isAtEnd2(Scanner *s, char * source) 
{
    return source[s->current] == NULL_TERMINATOR;
}

void printtokensv(Token **vtoken, int tokens_n)
{
    printf("Print tokens:\n");
    for (int i = 0; i < tokens_n; i++)
        printf("[%d] - lexeme(%s) - line(%d)\n", i, vtoken[i]->lexeme, vtoken[i]->line);
}

Token* scantokens(Scanner *s, int source_n, int tokens_n)
{
    //while(isatend(s->current, source_n) != 1)
    while (s->current >= source_n)
    {
        s->start = s->current;
        scantokens(s, source_n, tokens_n);
    };

    //s->vtokens[tokens_n] = newtoken(ENDOFFILE, NULL, 0, NULL, s->line);
    Token * newtk = newtoken(ENDOFFILE, NULL, 0, NULL, s->line);
    stack = pushf(newtk, stack);
    s->linkedtokens = stack;
    return s->linkedtokens;
}

// TODO: Mover para tokens.c
/*
Token** allocvtokens(int tokens_n)
{
    Token **v = (Token **)malloc(tokens_n * sizeof(Token *));
    if (v != NULL)
    {
        for (int i = 0; i < tokens_n; i++)
        {
            v[i] = (Token *)malloc(sizeof(Token));
            if (v[i] != NULL)
            {
                v[i]->lexeme = NULL;
                v[i]->line = 1;
                v[i]->type = NONE;
            }
            else { exit(EX_MEMALLOC);}
        }
    }
    else
    { exit(EX_MEMALLOC);}
    return v;
}
*/

int peek(Scanner * s, char * source)
{
    if (isAtEnd2(s, source)) return '\0';
    return source[s->current];
}

void string(Scanner * s, char * source)
{
    while(peek(s, source) != '"' && !isAtEnd2(s, source))
    {
        if (peek(s, source) == '\n')
            s->line++;
        advance(s, source);
    }

    if (isAtEnd2(s, source)) 
    {
        printf("Unterminated string at %d.\n", s->line);
        return;
    }

    advance(s, source);
    char * value = substring(source, s->start + 1, s->current - 1);
    addtoken(s, value, STRING);
}

int isDigit(char c)
{
    return c >= '0' && c <= '9';
}

char peekNext(Scanner * s, char * source)
{
    if (s->current + 1 >= strlen(source)) return NULL_TERMINATOR;
    return source[s->current + 1];
}

void number(Scanner * s, char * source)
{
    while(isDigit(peek(s, source))) advance(s, source);

    if (peek(s, source) == '.' && isDigit(peekNext(s, source))) {
        advance(s, source);

        while(isDigit(peek(s, source))) advance(s, source);
    }

    char * value = substring(source, s->start, s->current);
    /*

    Corrigir depois para algo equivalente a:

        addToken(NUMBER,
        Double.parseDouble(source.substring(start, current)));
    */
    //addtoken(s, strtod(value), NUMBER);
    addtoken(s, value, NUMBER); 
}

int isAlpha(char c) {

    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
        return U_TRUE;
    return U_FALSE;
}

int isAlphaNUmeric(char c)
{
    if (isAlpha(c) || isDigit(c))
        return U_TRUE;
    return U_FALSE;
}

void identifier(Scanner * s, char * source) {
    while(isAlphaNUmeric(peek(s, source)))
        advance(s, source);
    addToken(IDENTIFIER);
}

void scantoken(Scanner *s, char *source, Token* stack)
{
    char c = advance(s, source);
    switch (c)
    {
    case '(':
        addtoken(s, source, LEFT_PAREN);
        break;
    case ')':
        addtoken(s, source, RIGHT_PAREN);
        break;
    case '{':
        addtoken(s, source, LEFT_BRACE);
        break;
    case '}':
        addtoken(s, source, RIGHT_BRACE);
        break;
    case ',':
        addtoken(s, source, COMMA);
        break;
    case '.':
        addtoken(s, source, DOT);
        break;
    case '-':
        addtoken(s, source, MINUS);
        break;
    case '+':
        addtoken(s, source, PLUS);
        break;
    case ';':
        addtoken(s, source, SEMICOLON);
        break;
    case '*':
        addtoken(s, source, STAR);
        break;
      case '!':
        addtoken(s, source, match(s, strlen(source), '=') ? BANG_EQUAL : BANG);
        break;
      case '=':
        addtoken(s, source, match(s, strlen(source),'=') ? EQUAL_EQUAL : EQUAL);
        break;
      case '<':
        addtoken(s, source, match(s, strlen(source),'=') ? LESS_EQUAL : LESS);
        break;
      case '>':
        addtoken(s, source, match(s, strlen(source),'=') ? GREATER_EQUAL : GREATER);
        break;
     case '/':
        if (match(s, strlen(source), '/'))
        { while(peek(s, source) == '\n' && !isAtEnd2(s, source)) advance(s, source);
        } else { addtoken(s, source, SLASH); }
        break;

      case ' ':
      case '\r':
      case '\t':
        // Ignore whitespace.
        break;

      case '\n':
        s->line++;
        break;

      case '"': string(s, source); break;
      case 'o':
        if (match(s, strlen(source), 'r')) {
            addtoken(s, source, OR);
        }
        break;

    default:
        if (isDigit(c))
        {
            number(s, source);
        } else if (isAlpha(c))
        {
            identifier();
        } 
        else {
            printf("Unexpected character at line %d.\n", s->line);
        }
        break;
    }
}

/*

Acessa o caractere na posição atual do current e 
em seguida incrementa o currence. Ele avança no fluxo de entrada (source)
nextchar == advance
*/
char advance(Scanner *s, char *source)
{
    return source[s->current++];
}

// "Sobrescrita" do metodo addtokenwliteral
void addtoken(Scanner *s, char *source, token_t type)
{
    addtokenwliteral(s, source, type, NULL);
}

void addtokenwliteral(Scanner *s, char *source, token_t type, Object *literal)
{
    char *txt = substring(source, s->start, s->current);
    Token *newtk = newtoken(type, txt, strlen(txt), literal, s->line);
    stack = pushf(newtk, stack);
    s->linkedtokens = stack;
}

int match(Scanner * s, int source_n, char expected) 
{
    if (s->current >= source_n) return FALSE;
    if (s->current != expected) return FALSE;
    s->current++;
    return TRUE;
}

