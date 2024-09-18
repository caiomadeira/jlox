/*

https://gist.github.com/bojanrajkovic/831993

*/
#pragma once // Protege os arquivos de multiplos imports
#include<stdio.h>
#include<stdlib.h>

//verificar depois
//typedef unsigned char Byte;

// from sysexits.h
#define EX_USAGE	64	/* command line usage error */
#define EX_DATAERR	65	/* data format error */
// my 
#define EX_MEMALLOC 2 /* memory allocation error */

#define NULL_TERMINATOR '\0'
#define U_TRUE 1
#define U_FALSE 0


typedef enum {
    INT_T, FLOAT_T, CHAR_T,
} PrimitiveData;

typedef struct {
    void * data;
    char type;
} Object;

FILE * openf(const char * filename, const char* mode);
char * allocstr(int n);
void * convert_t(void * input, PrimitiveData type);