#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "value.h"

int main(int agrc, char *argv[]) {
    Chunk chunk;
    Chunk *ch = &chunk;
    initChunk(ch);

    writeChunk(ch, OP_RETURN, 1);
    int constant = addConstant(ch, 11.76);
    writeChunk(ch, OP_CONSTANT, 1);
    writeChunk(ch, constant, 1);

    disassembleChunk(ch, "test chunk");

    freeChunk(ch);
    return 0;
}
