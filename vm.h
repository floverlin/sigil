#ifndef sil_vm_h
#define sil_vm_h

#include "table.h"
#include "value.h"
#include "object.h"

#define FRAMES_MAX 64 
#define STACK_MAX (FRAMES_MAX * UINT8_COUNT)

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

typedef struct {
    ObjFunction *function;
    uint8_t *pc;
    Value *slots;
} CallFrame;

typedef struct {
    Value stack[STACK_MAX];
    Value *stackTop;

    CallFrame frames[FRAMES_MAX];
    int frameCount;

    Obj *objects;
    Table strings;
    Table globals;
} VM;

void initVM(void);
void freeVM(void);

InterpretResult interpret(char *source);

void push(Value value);
Value pop(void);

extern VM vm;

#endif