/*
Module that's define our code representation.
"Chunks" refer to sequences of bytecode
*/
#ifndef cmarte_chunk_h
#define cmarte_chunk_h

#include "common.h"

/*

IN our bytecode format, each instruction has a one-byte operation code
(opcode). THat number controls what kind of instruction we're dealing with - add,
 subtract, look up variable, etc. We define those here.
*/
typedef enum {
    OP_RETURN, // Return for the current function
} opcode;

#endif

// Dynamic array of instructions
/*
Bytecode is a series of instructions. Eventually, we'll store some other data along
with the instructions., lets create a struct to hold it all.

Dynamic arrays is:
    - Cache-friendly, dense storage;
    - O(1) indexed element lookup; O(1) appending to the end of the array;
*/
typedef struct {
    int count;
    int capacity;
    uint8_t* code;
} Chunk;
