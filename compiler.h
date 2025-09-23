#ifndef sil_compiler_h
#define sil_compiler_h

#include "lexer.h"
#include "object.h"
#include "vm.h"

typedef enum {
    PREC_NONE,
    PREC_ASSIGNMENT,  // =
    PREC_OR,          // or
    PREC_AND,         // and
    PREC_EQUALITY,    // == !=
    PREC_COMPARISON,  // < > <= >=
    PREC_TERM,        // + -
    PREC_FACTOR,      // * /
    PREC_UNARY,       // ! -
    PREC_CALL,        // . ()
    PREC_PRIMARY
} Precedence;

typedef enum {
    TYPE_FUNCTION,
    TYPE_SCRIPT,
} FunctionType;

typedef struct {
    Token name;
    int depth;
} Local;

typedef struct Compiler {
    struct Compiler *enclosing;
    ObjFunction *function;
    FunctionType type;
    Local locals[UINT8_COUNT];
    int localCount;
    int scopeDepth;
} Compiler;

typedef void (*ParseFn)(bool canAssign);

typedef struct {
    ParseFn prefix;
    ParseFn infix;
    Precedence precedence;
} ParseRule;

ObjFunction *compile(const char *source);

#endif