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
 * File: aby.h
 * Description: 
 * Author: Lovro Kalinovcic
 * 
 */

#ifndef ABY_H_
#define ABY_H_

#include <stdlib.h>

#include "atype.h"
#include "bytecode.h"
#include "error.h"
#include "memory.h"
#include "native.h"
#include "thread.h"

struct AVM_ABY
{
    AVM_u32 nativec;
    struct AVM_native** nativev;
    AVM_u32 bcodec;
    struct AVM_bytecode** bcodev;

    AVM_u32 threadc;
    struct AVM_thread* threadv;
    struct AVM_memory* globalmem;

    AVM_u32 wait;
};

struct AVM_ABY* AVM_ABY_new(FILE* pF);
void AVM_ABY_free(struct AVM_ABY* aby);

#endif /* ABY_H_ */
