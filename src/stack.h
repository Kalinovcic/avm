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
 * File: struct.h
 * Description: 
 * Author: Lovro Kalinovcic
 * 
 */

#ifndef STRUCT_H_
#define STRUCT_H_

#include <stdlib.h>
#include <string.h>

#include "atype.h"
#include "error.h"

struct AVM_stack
{
    AVM_u8* sb;
    AVM_u8* se;
    AVM_u8* sp;
};

struct AVM_stack* AVM_stack_new(AVM_size size);
void AVM_stack_free(struct AVM_stack* stack);

void AVM_stack_push(struct AVM_stack* stack, void* ptr, AVM_size size);
void AVM_stack_pop(struct AVM_stack* stack, void* ptr, AVM_size size);

#endif /* STRUCT_H_ */
