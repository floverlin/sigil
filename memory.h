#ifndef sil_memory_h
#define sil_memory_h

#include "common.h"

#define GROW_CAPACITY(cap) ((cap) < 8 ? 8 : (cap) * 2)

#define GROW_ARRAY(type, ptr, oldCount, newCount)      \
    (type *)reallocate(ptr, sizeof(type) * (oldCount), \
                       sizeof(type) * (newCount))

#define FREE_ARRAY(type, ptr, oldCount) \
    reallocate((ptr), sizeof(type) * (oldCount), 0)

#define FREE(type, pointer) reallocate(pointer, sizeof(type), 0)

#define ALLOCATE(type, length) \
    (type *)reallocate(NULL, 0, sizeof(type) * length)

void *reallocate(void *ptr, size_t oldSize, size_t newSize);

void freeObjects(void);

#endif