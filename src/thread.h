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

struct AVM_thread
{
    struct AVM_bytecode* bcode;
    AVM_u8* pc;
};

struct AVM_thread* AVM_thread_new();
void AVM_thread_free(struct AVM_thread* thread);

void AVM_thread_setbc(struct AVM_thread* thread, struct AVM_bytecode* bcode);
void AVM_thread_jump(struct AVM_thread* thread, AVM_size pc);

#endif /* THREAD_H_ */
