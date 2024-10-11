/*
Module that's define our code representation.
"Chunks" refer to sequences of bytecode
*/
#ifndef cmarte_chunk_h
#define cmarte_chunk_h

#include "common.h"
#include "value.h"
#include "memory.h"

/*

IN our bytecode format, each instruction has a one-byte operation code
(opcode). THat number controls what kind of instruction we're dealing with - add,
 subtract, look up variable, etc. We define those here.
*/
typedef enum {
    OP_CONSTANT,
    OP_CONSTANT_LONG,
    OP_RETURN, // Return for the current function
} opcode;



// Dynamic array of instructions
/*
Bytecode is a series of instructions. Eventually, we'll store some other data along
with the instructions., lets create a struct to hold it all.

Dynamic arrays is:
    - Cache-friendly, dense storage;
    - O(1) indexed element lookup; O(1) appending to the end of the array;
*/

typedef struct {
    int offset;
    int line;
} LineStart;

typedef struct {
    int count; // how many of those allocated entries are actually in use
    int capacity; // Number of elements in the array we have allocated
    uint8_t* code;
    //int* lines; // this separted array is for lines numbers when a error occurs in runtime
    int lineCount;
    int lineCapacity;
    LineStart *lines;
    ValueArray constants; // Store chunk's constantes
} Chunk;

// C doesn't have constructores, so we declare a function to initialize a new chunk

void initChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
int addConstant(Chunk* chunk, Value value);
void freeChunk(Chunk* chunk);
int getLine(Chunk* chunk, int instruction); // aux func
void writeConstant(Chunk* chunk, Value value, int line);

#endif
