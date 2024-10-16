#include <stdio.h>

#include "common.h"
#include "debug.h"
#include "vm.h"

/*
We declare a single global VM object
because eventually this module is going to have
more functions and it would be a chora to pass around a pointer
to the VM to all of them.

Everything bad you've heard about global variables is still true
qhen programming in the large
*/
VM vm;

static void resetStack() {
    vm.stackTop = vm.stack;
}

void initVM()
{
    resetStack();
}

void freeVM()
{

}

void push(Value value)
{
    *vm.stackTop = value;
    vm.stackTop++; // incrementamos o slot para apontar para o proximo disponivel
}

/*
Nos nao precisamos explicitamente remove-lo do array, apenas movemos o stackTop
para tras. Isso é o suficiente para marcar que o slot nao esta mais sendo usado
*/
Value pop() {
    vm.stackTop--;
    return *vm.stackTop;
}

/*
When the interpreter executes a user’s program, 
it will spend something like 90% of its time inside run(). 
It is the beating heart of the VM.
*/
static InterpretResult run()
{
    #define READ_BYTE() (*vm.ip++) // macro reads the byte currently pointed at by ip and then advances the instruction pointer. 
// The first byte of any instruction is the opcode. Given a numeric opcode, we need to get to the right C code that implements that instruction’s semantics. This process is called decoding or dispatching the instruction.
    
    // Reads the next byte from the bytecode, treats the resulting number as an index. and looks up the corresponding Value in the chunk's constant table.
    #define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

    for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
// (int)(vm.ip - vm.chunk->code): pointer math to convert ip back to a relative offset from the beginning of the bytecode
    disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif
        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT:
                Value constant = READ_CONSTANT();
                printValue(constant);
                printf("\n");
                break;
            case OP_RETURN: {
                return INTERPRET_OK;
            }
        }
    }
    #undef READ_BYTE
    #undef READ_CONSTANT
}

InterpretResult interpret(Chunk* chunk)
{
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;
    return run();
}