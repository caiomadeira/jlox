#include "utils.h"

FILE * openf(const char * filename, const char* mode)
{
    FILE * f = fopen(filename, mode);
    if (f == NULL) { exit(EX_MEMALLOC); }
    return f;
}

char * allocstr(int n)
{
    char * buffer = (char *)malloc(n*sizeof(char) + 1);
    if (buffer == NULL) { exit(EX_MEMALLOC); }
    return buffer;
}

void * convert_t(void * input, PrimitiveData type)
{
    void * output = NULL;
    switch (type)
    {
    case INT_T: {
        int * buffer = (int*)malloc(sizeof(int));
        *buffer = *(int*)input;
        output = buffer;
        break;
    }

    case CHAR_T: {
        char * buffer = (char*)malloc(sizeof(char));
        *buffer = *(char*)input;
        output = buffer;
        break;
    }
    case FLOAT_T: {
        float * buffer = (float*)malloc(sizeof(float));
        *buffer = *(float*)input;
        output = buffer;
        break;
    }
    
    default:
        break;
    }
    return output;
}

/*
FUncao para criar uma substring de source entre start (inclusivo) e end (exclusivo)
*/
char* substring(const char* source, int start, int end)
{
    if (start < 0 || end > strlen(source) || start > end)
        return NULL;
    // tamanho da nova substring
    int len = end - start;
    char * result = allocstr(len);
    strncpy(result, source + start, len);
    result[len] = '\0';
    return result;
}