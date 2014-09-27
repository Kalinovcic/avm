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
 * File: bytecode.h
 * Description: 
 * Author: Lovro Kalinovcic
 * 
 */

#ifndef BYTECODE_H_
#define BYTECODE_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "atype.h"
#include "error.h"

struct AVM_bytecode
{
    AVM_u8* bcb;
    AVM_u8* bce;
};

struct AVM_bytecode* AVM_bytecode_new(AVM_size size);
void AVM_bytecode_free(struct AVM_bytecode* bcode);

void AVM_bytecode_load(struct AVM_bytecode* bcode, FILE* pF);
void AVM_bytecode_next(struct AVM_bytecode* bcode, AVM_u8** pc, void* ptr, AVM_size size);

#endif /* BYTECODE_H_ */
