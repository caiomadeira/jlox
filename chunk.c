#include<stdlib.h>

#include "chunk.h"

void initChunk(Chunk* chunk)
{
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    chunk->lineCount = 0;
    chunk->lineCapacity = 0;
    chunk->lines = NULL;
    initValueArray(&chunk->constants);
}

// Binary search
int getLine(Chunk* chunk, int instruction)
{
    int start = 0;
    int end = chunk->lineCount - 1;

    for (;;) {
        int mid = (start + end)/2;
        LineStart* line = &chunk->lines[mid];
        if (instruction < line->offset) {
            end = mid - 1;
        } else if (mid == chunk->lineCount - 1 || 
        instruction < chunk->lines[mid + 1].offset) 
        {
            return line->line;
        } else {
            start = mid + 1;
        }
    }
}

void writeChunk(Chunk* chunk, uint8_t byte, int line)
{
    if (chunk->capacity < chunk->count + 1)
    {
        int oldcapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldcapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldcapacity, chunk->capacity);
        //chunk->lines = GROW_ARRAY(int, chunk->lines, oldcapacity, chunk->capacity);
    }
    chunk->code[chunk->count] = byte;
    //chunk->lines[chunk->count] = line;
    chunk->count++;

    // Checa se estamos na mesma linha
    if (chunk->lineCount > 0 && chunk->lines[chunk->lineCount - 1].line == line)
        return;
    
    // se nao, append uma nova linha
    if (chunk->lineCapacity < chunk->lineCount + 1)
    {
        int oldcapacity = chunk->lineCapacity;
        chunk->lineCapacity = GROW_CAPACITY(oldcapacity);
        chunk->lines = GROW_ARRAY(LineStart, chunk->lines, oldcapacity, chunk->lineCapacity);
    }

    LineStart* lineStart = &chunk->lines[chunk->lineCount++];
    lineStart->offset = chunk->count - 1;
    lineStart->line = line;
}

int addConstant(Chunk* chunk, Value value)
{
    writeValueArray(&chunk->constants, value);
// we return the index where the constant was appended so that we can locate that same constant later
    return chunk->constants.count - 1; 
}

void writeConstant(Chunk* chunk, Value value, int line)
{
    int index = addConstant(chunk, value);
    if (index < 256) {
        writeChunk(chunk, OP_CONSTANT, line);
        writeChunk(chunk, (uint8_t)index, line);
    } else {
        writeChunk(chunk, OP_CONSTANT_LONG, line);
        writeChunk(chunk, (uint8_t)(index & 0xff), line);
        writeChunk(chunk, (uint8_t)(index >> 8) & 0xff, line);
        writeChunk(chunk, (uint8_t)(index >> 16) & 0xff, line);
    }
}

void freeChunk(Chunk* chunk) 
{
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(LineStart, chunk->lines, chunk->lineCapacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}
