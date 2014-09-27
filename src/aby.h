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

#include "atype.h"
#include "bytecode.h"
#include "error.h"
#include "memory.h"
#include "thread.h"

struct AVM_ABY
{
    AVM_u32 threadc;
    AVM_u32 bcodec;

    struct AVM_thread* threadv;
    struct AVM_bytecode* bcodev;

    struct AVM_memory* globalmem;
};

#endif /* ABY_H_ */
