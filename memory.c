#include <stdlib.h>

#include "memory.h"

void* reallocate(void* pointer, size_t oldsize, size_t newsize)
{
    if (newsize == 0) // newsize == 0 we make an deallocation
    { free(pointer); return NULL; }
    void* result = realloc(pointer, newsize);
    if (result == NULL) exit(1);
    return result;
}