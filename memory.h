#ifndef RMEMORY_H
#define RMEMORY_H

#include "def.h"
#include <string.h>
typedef struct MemStack
{
    void *stackStart;
    void *stackTop;
    usize defaultAlign;
    usize stackSize;
} MemStack;

typedef struct MemStackFrame
{
    void *frame;
} MemStackFrame;

static uintptr_t PointerToInteger(void *ptr)
{
    uintptr_t ptrInt = 0;
    memcpy(&ptrInt, &ptr, sizeof(ptrInt));
    return ptrInt;
}

static void *IntegerToPointer(uintptr_t i)
{
    void *ptr;
    memcpy(&ptr, &i, sizeof(ptr));
    return ptr;
}

void *AllocFromMemStackAligned(MemStack *stack, usize numElems, usize elemSize, usize elemAlign);
void *AllocFromMemStack(MemStack *stack, usize numElems, usize elemSize);

MemStackFrame SaveMemStackFrame(MemStack *stack);

void RestoreMemStackFrame(MemStack *stack, MemStackFrame frame);

MemStack InitializeMemstack(void *stackMem, usize stackSize, usize alignment);
#endif
