#ifndef sil_vm_h
#define sil_vm_h

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

typedef struct {
    Value stack[STACK_MAX];
    Value *stackTop;
    uint8_t *pc;
    Chunk *chunk;
    Obj *objects;
} VM;

void initVM(void);
void freeVM(void);

InterpretResult interpret(char *source);

void push(Value value);
Value pop(void);

extern VM vm;

#endif