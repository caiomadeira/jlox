#ifndef cmarte_vm_h
#define cmarte_vm_h

#include "chunk.h"

typedef struct {
    Chunk* chunk;
    // keeps track the location of the instruction currently being executed. Other functions will need to access it.
    /*
        we use an actual real C pointer pointing right into the middle of the bytecode array
        instead of something like an integer index because it's faster to dereference a pointer
        than look up an element in an array by index.
        IP = Instruction Pointer. It's a pattern
        x86, x64, and the CLR call it “IP”. 68k, PowerPC, ARM, p-code, and the JVM call it “PC”, for program counter.
    */
    uint8_t* ip;
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVM();
void freeVM();
InterpretResult interpret(Chunk* chunk);

#endif
