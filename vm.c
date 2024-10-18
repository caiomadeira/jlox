#include <stdio.h>

#include "common.h"
#include "compiler.h"
#include "debug.h"
#include "vm.h"
#include "value.h"

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

    // depois transformar em função
    #define BINARY_OP(op) \
        do { \
            double b = pop(); \
            double a = pop(); \
            push(a op b); \
        } while (false)

    for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
    printf("        ");
    for(Value* slot = vm.stack; slot < vm.stackTop; slot++)
    {
        printf("[ ");
        printValue(*slot);
        printf(" ]");
    }
    printf("\n");
    // (int)(vm.ip - vm.chunk->code): pointer math to convert ip back to a relative offset from the beginning of the bytecode
    disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif
        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            }
            case OP_ADD:    BINARY_OP(+); break;
            case OP_MULTIPLY: BINARY_OP(*); break;
            case OP_DIVIDE:   BINARY_OP(/); break;
            case OP_NEGATE: push(-pop()); break;
            case OP_RETURN: {
                printValue(pop());
                printf("\n");
                return INTERPRET_OK;
            }
        }
    }
    #undef READ_BYTE
    #undef READ_CONSTANT
    #undef BINARY_OP
}
/*
We create a new empty chunk and pass it over to the compiler. 
The compiler will take the user’s program and fill up the chunk with 
bytecode. At least, that’s what it will do if the program doesn’t have 
any compile errors. If it does encounter an error, compile() returns 
false and we discard the unusable chunk.

Otherwise, we send the completed chunk over to the VM 
to be executed. When the VM finishes, we free the chunk 
and we’re done. As you can see, the signature to compile() is 
different now.


*/
InterpretResult interpret(const char* source)
{
    Chunk chunk;
    initChunk(&chunk);

    if (!compile(source, &chunk)) {
        freeChunk(&chunk);
        return INTERPRET_COMPILE_ERROR;
    }

    vm.chunk = &chunk;
    vm.ip = vm.chunk->code;

    InterpretResult result = run();

    freeChunk(&chunk);
    return result;
}