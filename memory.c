/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "memory.h"

void *AllocFromMemStack(MemStack *stack, usize numElems, usize elemSize)
{
    return AllocFromMemStackAligned(stack, numElems, elemSize, stack->defaultAlign);
}

MemStackFrame SaveMemStackFrame(MemStack *stack)
{
    MemStackFrame ret = {stack->stackTop};
    return ret;
}

void RestoreMemStackFrame(MemStack *stack, MemStackFrame frame)
{
    stack->stackTop = frame.frame;
}

void *AllocFromMemStackAligned(MemStack *stack, usize numElems, usize elemSize, usize elemAlign)
{
    uintptr_t stackTop = PointerToInteger(stack->stackTop);
    if (stackTop % elemAlign != 0)
    {
        stackTop += elemAlign - stackTop % elemAlign;
    }

    usize allocSize = elemSize * numElems;
    if (stackTop + allocSize - PointerToInteger(stack->stackStart) > stack->stackSize)
    {
        return NULL;
    }
    stack->stackTop = IntegerToPointer(stackTop + allocSize);
    return IntegerToPointer(stackTop);
}

MemStack InitializeMemstack(void *stackMem, usize stackSize, usize alignment)
{
    MemStack ret = {stackMem, stackMem, alignment, stackSize};
    return ret;
}
