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
 * File: memory.c
 * Description: 
 * Author: Lovro Kalinovcic
 * 
 */

#include "memory.h"

struct AVM_memory* AVM_memory_new(AVM_size size)
{
    struct AVM_memory* memory = malloc(sizeof(struct AVM_memory));
    if(!memory)
        AVM_abort("out of memory", AVM_ERRNO_OUTOFMEM);
    memory->memb = malloc(size);
    if(!memory->memb)
        AVM_abort("out of memory", AVM_ERRNO_OUTOFMEM);
    memory->meme = memory->memb + size;
    return memory;
}

void AVM_memory_free(struct AVM_memory* memory)
{
    free(memory->memb);
    free(memory);
}

inline int AVM_in_range(struct AVM_memory* memory, AVM_u8* addr)
{
    return (memory->memb <= addr) && (addr < memory->meme);
}

inline void AVM_range_check(struct AVM_memory* memory, AVM_size addr)
{
    if(!AVM_in_range(memory, memory->memb + addr))
        AVM_abort("segmentation fault", AVM_ERRNO_SEGMNFLT);
}

void AVM_memory_get(struct AVM_memory* memory, AVM_size addr, AVM_size size, void* ptr)
{
    AVM_range_check(memory, addr);
    AVM_range_check(memory, addr + size - 1);
    memcpy(ptr, memory->memb + addr, size);
}

void AVM_memory_set(struct AVM_memory* memory, AVM_size addr, AVM_size size, void* ptr)
{
    AVM_range_check(memory, addr);
    AVM_range_check(memory, addr + size - 1);
    memcpy(memory->memb + addr, ptr, size);
}

void AVM_memory_heapalloc(AVM_size size, AVM_u64* pointer)
{
    *pointer = (AVM_u64) malloc(size);
    if(!*pointer)
        AVM_abort("out of memory", AVM_ERRNO_OUTOFMEM);
}

void AVM_memory_heapfree(AVM_u64 pointer)
{
    free((void*) pointer);
}

void AVM_memory_heapget(AVM_u64 pointer, void* ptr, AVM_size size)
{
    memcpy(ptr, (void*) pointer, size);
}

void AVM_memory_heapset(AVM_u64 pointer, void* ptr, AVM_size size)
{
    memcpy((void*) pointer, ptr, size);
}
