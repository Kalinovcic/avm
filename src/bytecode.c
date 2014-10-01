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
 * File: bytecode.c
 * Description: 
 * Author: Lovro Kalinovcic
 * 
 */

#include "bytecode.h"

struct AVM_bytecode* AVM_bytecode_new(AVM_size codesize, AVM_size memsize)
{
    struct AVM_bytecode* bcode = malloc(sizeof(struct AVM_bytecode));
    if(!bcode)
        AVM_abort("out of memory", AVM_ERRNO_OUTOFMEM);
    bcode->bcb = malloc(codesize);
    if(!bcode->bcb)
        AVM_abort("out of memory", AVM_ERRNO_OUTOFMEM);
    bcode->bce = bcode->bcb + codesize;

    bcode->memsize = memsize;
    return bcode;
}

void AVM_bytecode_free(struct AVM_bytecode* bcode)
{
    free(bcode->bcb);
    free(bcode);
}

void AVM_bytecode_load(struct AVM_bytecode* bcode, FILE* pF)
{
    AVM_size n = bcode->bce - bcode->bcb;
    AVM_size rn = fread(bcode->bcb, 1, n, pF);
    if(n != rn)
        AVM_abort("failed to load bytecode", AVM_ERRNO_BCODLOAD);
}

void AVM_bytecode_next(struct AVM_bytecode* bcode, AVM_u8** pc, void* ptr, AVM_size size)
{
    if(*pc < bcode->bcb || *pc >= bcode->bce)
        AVM_abort("invalid PC", AVM_ERRNO_BCINVLPC);
    if((*pc + size) > bcode->bce)
        AVM_abort("unexpected EOF", AVM_ERRNO_BCODEEOF);
    memcpy(ptr, *pc, size);
    *pc += size;
}
