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
 * File: thread.h
 * Description: 
 * Author: Lovro Kalinovcic
 * 
 */

#ifndef THREAD_H_
#define THREAD_H_

#include "atype.h"
#include "bytecode.h"
#include "error.h"
#include "stack.h"

#define AVM_RETURN_MAXDEPTH             (2048)
#define AVM_RETURN_UNITSIZE             (sizeof(void*) * 3)
#define AVM_RETURNSTACK_SIZE            (AVM_RETURN_MAXDEPTH * AVM_RETURN_UNITSIZE)

struct AVM_thread
{
    struct AVM_stack* stack;
    struct AVM_stack* returnstack;
    AVM_u32 returnc;

    AVM_u8* pc;
    struct AVM_bytecode* bcode;
    struct AVM_memory* localmem;

    AVM_u8 wait;

    struct AVM_thread* prev;
    struct AVM_thread* next;
};

struct AVM_thread* AVM_thread_new();
void AVM_thread_free(struct AVM_thread* thread);

void AVM_thread_push(struct AVM_thread* thread, struct AVM_bytecode* bcode);
void AVM_thread_pop(struct AVM_thread* thread);

void AVM_thread_update_wait(struct AVM_thread* thread);

#endif /* THREAD_H_ */
