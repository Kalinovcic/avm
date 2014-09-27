/* 
 * Copyright (C) 2014 Lovro Kalinovcic
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * 
 * File: struct.c
 * Description: 
 * Author: Lovro Kalinovcic
 * 
 */

#include "stack.h"

struct AVM_stack* AVM_stack_new(AVM_size size)
{
    struct AVM_stack* stack = malloc(sizeof(struct AVM_stack));
    stack->sb = malloc(size);
    stack->se = stack->sb + size;
    stack->sp = stack->sb;
    return stack;
}

void AVM_stack_free(struct AVM_stack* stack)
{
    free(stack);
}

inline int AVM_is_overflow(struct AVM_stack* stack, AVM_size amount)
{
    return (stack->sp + amount) > stack->se;
}

inline int AVM_is_underflow(struct AVM_stack* stack, AVM_size amount)
{
    return (stack->sp - amount) < stack->sb;
}

inline void AVM_overflow_check(struct AVM_stack* stack, AVM_size amount)
{
    if(AVM_is_overflow(stack, amount))
        AVM_abort("stack overflow", AVM_ERRNO_OVERFLOW);
}

inline void AVM_underflow_check(struct AVM_stack* stack, AVM_size amount)
{
    if(AVM_is_underflow(stack, amount))
        AVM_abort("stack underflow", AVM_ERRNO_UNDRFLOW);
}

void AVM_stack_push(struct AVM_stack* stack, void* ptr, AVM_size size)
{
    AVM_overflow_check(stack, size);
    memcpy(stack->sp, ptr, size);
    stack->sp += size;
}

void AVM_stack_pop(struct AVM_stack* stack, void* ptr, AVM_size size)
{
    AVM_underflow_check(stack, size);
    stack->sp -= size;
    memcpy(ptr, stack->sp, size);
}
