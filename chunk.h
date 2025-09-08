#ifndef sil_chunk_h
#define sil_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
  OP_RETURN,
  OP_CONSTANT,
} op_code;

typedef struct {
  int count;
  int capacity;
  int *lines;
  uint8_t *code;
  ValueArray constants;
} Chunk;

void initChunk(Chunk *chuck);
void writeChunk(Chunk *chunk, uint8_t byte, int line);
int addConstant(Chunk *chunk, Value value);
void freeChunk(Chunk *chunk);

#endif