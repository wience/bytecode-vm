#ifndef npa_vm_h
#define npa_vm_h

#include "chunk.h"

typedef struct
{
    Chunk *chunk;
} VM;

typedef enum
{
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVM();
void freeVM();

#endif