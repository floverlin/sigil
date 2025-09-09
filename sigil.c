#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "value.h"
#include "vm.h"

int main(int agrc, char *argv[]) {
    initVM();

    Chunk chunk;
    Chunk *ch = &chunk;
    initChunk(ch);

    int constant;

    constant = addConstant(ch, 11.76);
    writeChunk(ch, OP_CONSTANT, 1);
    writeChunk(ch, constant, 1);

    constant = addConstant(ch, 11);
    writeChunk(ch, OP_CONSTANT, 2);
    writeChunk(ch, constant, 2);

    writeChunk(ch, OP_NEGATE, 2);

    writeChunk(ch, OP_ADD, 3);

    writeChunk(ch, OP_RETURN, 100);

    disassembleChunk(ch, "test chunk");

    interpret(ch);

    freeChunk(ch);
    freeVM();
    return 0;
}
