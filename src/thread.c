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
 * File: thread.c
 * Description: 
 * Author: Lovro Kalinovcic
 * 
 */

#include "thread.h"

struct AVM_thread* AVM_thread_new()
{
    struct AVM_thread* thread = malloc(sizeof(struct AVM_thread));
    thread->stack = AVM_stack_new(2048);        // FIX ME!!!  :'(
    thread->returnstack = AVM_stack_new(AVM_RETURNSTACK_SIZE);
    thread->returnc = 0;
    return thread;
}

void AVM_thread_free(struct AVM_thread* thread)
{
    AVM_stack_free(thread->stack);
    free(thread);
}

void AVM_thread_push(struct AVM_thread* thread, struct AVM_bytecode* bcode)
{
    if(thread->returnc)
    {
        AVM_stack_push(thread->returnstack, &thread->pc, sizeof(void*));
        AVM_stack_push(thread->returnstack, &thread->bcode, sizeof(void*));
        AVM_stack_push(thread->returnstack, &thread->localmem, sizeof(void*));
    }
    thread->returnc++;

    thread->pc = bcode->bcb;
    thread->bcode = bcode;
    thread->localmem = AVM_memory_new(bcode->memsize);
}

void AVM_thread_pop(struct AVM_thread* thread)
{
    AVM_memory_free(thread->localmem);

    thread->returnc--;
    if(thread->returnc)
    {
        AVM_stack_pop(thread->returnstack, &thread->localmem, sizeof(void*));
        AVM_stack_pop(thread->returnstack, &thread->bcode, sizeof(void*));
        AVM_stack_pop(thread->returnstack, &thread->pc, sizeof(void*));
    }
}

void AVM_thread_update_wait(struct AVM_thread* thread)
{

}

