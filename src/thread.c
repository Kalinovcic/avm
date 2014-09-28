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
    return thread;
}

void AVM_thread_free(struct AVM_thread* thread)
{
    free(thread);
}

void AVM_thread_setbc(struct AVM_thread* thread, struct AVM_bytecode* bcode)
{
    thread->bcode = bcode;
}

void AVM_thread_setpc(struct AVM_thread* thread, AVM_size pc)
{
    thread->pc = thread->bcode->bcb + pc;
}

void AVM_thread_setprev(struct AVM_thread* thread, struct AVM_thread* prev)
{
    thread->prev = prev;
}

void AVM_thread_setnext(struct AVM_thread* thread, struct AVM_thread* next)
{
    thread->next = next;
}

AVM_bool AVM_thread_eof(struct AVM_thread* thread)
{
    if(thread->pc == thread->bcode->bce) return AVM_TRUE;
    return AVM_FALSE;
}

void AVM_thread_nextrun(struct AVM_thread* thread)
{

}

void AVM_thread_update_wait(struct AVM_thread* thread)
{

}

