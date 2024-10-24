#include <stdio.h>

#include "memory.h"
#include "value.h"

void initValueArray(ValueArray* array)
{
    array->values = NULL;
    array->capacity = 0;
    array->count = 0;
}

void writeValueArray(ValueArray* array, Value value)
{
    if (array->capacity < array->count + 1)
    {
        int oldcapacity = array->capacity;
        array->capacity = GROW_CAPACITY(oldcapacity);
        array->values = GROW_ARRAY(Value, array->values, oldcapacity, array->capacity);
    }

    array->values[array->count] = value;
    array->count++;
}

void freeValueArray(ValueArray* array)
{
    FREE_ARRAY(Value, array->values, array->capacity);
    initValueArray(array);
}

void printValue(Value value)
{
    switch(value.type)
    {
        case VAL_BOOL:
            printf(AS_BOOL(value) ? "true" : "false");
            break;
        case VAL_NIL: printf("nil"); break;
        case VAL_NUMBER: printf("%g", AS_NUMBER(value)); break;
    }
}
/*
First, we check the types. If the Values have different types, 
they are definitely not equal. Otherwise, we unwrap the two Values 
and compare them directly.

For each value type, we have a separate case that handles comparing 
the value itself. Given how similar the cases are, you might wonder 
why we can’t simply memcmp() the two Value structs and be done with it. 
The problem is that because of padding and different-sized union fields, 
a Value contains unused bits. C gives no guarantee about what is in those, 
so it’s possible that two equal Values actually differ in memory that isn’t used.

*/
bool valuesEqual(Value a, Value b) {
  if (a.type != b.type) return false;
  switch (a.type) {
    case VAL_BOOL:   return AS_BOOL(a) == AS_BOOL(b);
    case VAL_NIL:    return true;
    case VAL_NUMBER: return AS_NUMBER(a) == AS_NUMBER(b);
    default:         return false; // Unreachable.
  }
}