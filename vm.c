#include "common.h"
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

void initVM()
{

}

void freeVM()
{

}

/*
When the interpreter executes a user’s program, 
it will spend something like 90% of its time inside run(). 
It is the beating heart of the VM.
*/
static InterpretResult run()
{
    #define READ_BYTE() (*vm.ip++) // macro reads the byte currently pointed at by ip and then advances the instruction pointer. 
T// The first byte of any instruction is the opcode. Given a numeric opcode, we need to get to the right C code that implements that instruction’s semantics. This process is called decoding or dispatching the instruction.
    for (;;) {
        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_RETURN: {
                return INTERPRET_OK;
            }
        }
    }
    #undef READ_BYTE
}

InterpretResult interpret(Chunk* chunk)
{
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;
    return run();
}