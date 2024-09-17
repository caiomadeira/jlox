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
    case INT_T:
        int * buffer = (int*)malloc(sizeof(int));
        output = buffer;
        break;

    case CHAR_T:
        int * buffer = (char*)malloc(sizeof(char));
        output = buffer;
        break;

    case FLOAT_T:
        int * buffer = (float*)malloc(sizeof(float));
        output = buffer;
        break;
    
    default:
        break;
    }

    return output;
}