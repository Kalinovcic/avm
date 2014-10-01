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
 * File: memory.h
 * Description: 
 * Author: Lovro Kalinovcic
 * 
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#include <stdlib.h>
#include <string.h>

#include "atype.h"
#include "error.h"

struct AVM_memory
{
    AVM_u8* memb;
    AVM_u8* meme;
};

struct AVM_memory* AVM_memory_new(AVM_size size);
void AVM_memory_free(struct AVM_memory* memory);

void AVM_memory_get(struct AVM_memory* memory, AVM_size addr, AVM_size size, void* ptr);
void AVM_memory_set(struct AVM_memory* memory, AVM_size addr, AVM_size size, void* ptr);

void AVM_memory_heapalloc(AVM_size size, AVM_u64* pointer);
void AVM_memory_heapfree(AVM_u64 pointer);
void AVM_memory_heapget(AVM_u64 pointer, void* ptr, AVM_size size);
void AVM_memory_heapset(AVM_u64 pointer, void* ptr, AVM_size size);

#endif /* MEMORY_H_ */
