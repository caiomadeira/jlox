/*

    lower-level memory operations

*/

#ifndef cmarte_memory_h
#define cmarte_memory_h

#include "common.h"

/*
THis macro calculates a new capacity based on a
given current capacity. Its important that it scales
based on the old size. We grow by a factor of two. 
PS: 1.5x is another common choice
*/
#define GROW_CAPACITY(capacity) \
        ((capacity) < 8 ? 8 : (capacity) * 2)

/*
THis macro, basic, call the reallocate function.
THe macros itself takes care of getting the size
of array's element type and casting the resulting 
void* back to a pointer of the right type
*/

#define GROW_ARRAY(type, pointer, oldcount, newcount) \
    (type*)reallocate(pointer, sizeof(type) * (oldcount), \
    sizeof(type) * (newcount))

/*
Free the memory by passing in zero for the new size.

*/
#define FREE_ARRAY(type, pointer, oldcount) \
    reallocate(pointer, sizeof(type) * (oldcount), 0)

void* reallocate(void* pointer, size_t oldsize, size_t newsize);

#endif