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
 * File: exec.c
 * Description: 
 * Author: Lovro Kalinovcic
 * 
 */

#include "abyexe.h"

void AVM_ABYexecutor_nextrun(struct AVM_ABY* aby)
{
    AVM_u8 op;
    AVM_bytecode_next(aby->threadv->bcode, &aby->threadv->pc, &op, 1);
#if ABY_DEBUGOUT == 1
    printf("%.2x\n", op);
#endif

    switch(op)
    {
    case ABY_NOP:
    {
        break;
    }
    case ABY_PUSH4:
    {
        AVM_u32 value;
        AVM_bytecode_next(aby->threadv->bcode, &aby->threadv->pc, &value, 4);
        AVM_stack_push(aby->threadv->stack, &value, 4);
        break;
    }
    case ABY_PUSH8:
    {
        AVM_u64 value;
        AVM_bytecode_next(aby->threadv->bcode, &aby->threadv->pc, &value, 8);
        AVM_stack_push(aby->threadv->stack, &value, 8);
        break;
    }
    case ABY_POP4:
    {
        AVM_u32 value;
        AVM_stack_pop(aby->threadv->stack, &value, 4);
        break;
    }
    case ABY_POP8:
    {
        AVM_u64 value;
        AVM_stack_pop(aby->threadv->stack, &value, 8);
        break;
    }
    case ABY_LOAD4:
    {
        AVM_u32 mpos;
        AVM_u32 value;
        AVM_bytecode_next(aby->threadv->bcode, &aby->threadv->pc, &mpos, 4);
        AVM_stack_pop(aby->threadv->stack, &value, 4);
        AVM_memory_set(aby->threadv->localmem, mpos, 4, &value);
        break;
    }
    case ABY_LOAD8:
    {
        AVM_u32 mpos;
        AVM_u64 value;
        AVM_bytecode_next(aby->threadv->bcode, &aby->threadv->pc, &mpos, 4);
        AVM_stack_pop(aby->threadv->stack, &value, 8);
        AVM_memory_set(aby->threadv->localmem, mpos, 8, &value);
        break;
    }
    case ABY_FETCH4:
    {
        AVM_u32 mpos;
        AVM_u32 result;
        AVM_bytecode_next(aby->threadv->bcode, &aby->threadv->pc, &mpos, 4);
        AVM_memory_get(aby->threadv->localmem, mpos, 4, &result);
        AVM_stack_push(aby->threadv->stack, &result, 4);
        break;
    }
    case ABY_FETCH8:
    {
        AVM_u32 mpos;
        AVM_u64 result;
        AVM_bytecode_next(aby->threadv->bcode, &aby->threadv->pc, &mpos, 4);
        AVM_memory_get(aby->threadv->localmem, mpos, 8, &result);
        AVM_stack_push(aby->threadv->stack, &result, 8);
        break;
    }
    case ABY_LOADWIDE4:
    {
        AVM_u32 mpos;
        AVM_u32 value;
        AVM_bytecode_next(aby->threadv->bcode, &aby->threadv->pc, &mpos, 4);
        AVM_stack_pop(aby->threadv->stack, &value, 4);
        AVM_memory_set(aby->globalmem, mpos, 4, &value);
        break;
    }
    case ABY_LOADWIDE8:
    {
        AVM_u32 mpos;
        AVM_u64 value;
        AVM_bytecode_next(aby->threadv->bcode, &aby->threadv->pc, &mpos, 4);
        AVM_stack_pop(aby->threadv->stack, &value, 8);
        AVM_memory_set(aby->globalmem, mpos, 8, &value);
        break;
    }
    case ABY_FETCHWIDE4:
    {
        AVM_u32 mpos;
        AVM_u32 result;
        AVM_bytecode_next(aby->threadv->bcode, &aby->threadv->pc, &mpos, 4);
        AVM_memory_get(aby->globalmem, mpos, 4, &result);
        AVM_stack_push(aby->threadv->stack, &result, 4);
        break;
    }
    case ABY_FETCHWIDE8:
    {
        AVM_u32 mpos;
        AVM_u64 result;
        AVM_bytecode_next(aby->threadv->bcode, &aby->threadv->pc, &mpos, 4);
        AVM_memory_get(aby->globalmem, mpos, 8, &result);
        AVM_stack_push(aby->threadv->stack, &result, 8);
        break;
    }
    case ABY_VARPTR:
    {
        AVM_u32 mpos;
        AVM_u64 result;
        AVM_bytecode_next(aby->threadv->bcode, &aby->threadv->pc, &mpos, 4);
        AVM_memory_ptrof(aby->threadv->localmem, mpos, &result);
        AVM_stack_push(aby->threadv->stack, &result, 8);
        break;
    }
    case ABY_VARPTRWIDE:
    {
        AVM_u32 mpos;
        AVM_u64 result;
        AVM_bytecode_next(aby->threadv->bcode, &aby->threadv->pc, &mpos, 4);
        AVM_memory_ptrof(aby->globalmem, mpos, &result);
        AVM_stack_push(aby->threadv->stack, &result, 8);
        break;
    }
    case ABY_ALLOC:
    {
        AVM_u64 size;
        AVM_u64 pointer;
        AVM_stack_pop(aby->threadv->stack, &size, 8);
        AVM_memory_heapalloc(size, &pointer);
        AVM_stack_push(aby->threadv->stack, &pointer, 8);
        break;
    }
    case ABY_FREE:
    {
        AVM_u64 pointer;
        AVM_stack_pop(aby->threadv->stack, &pointer, 8);
        AVM_memory_heapfree(pointer);
        break;
    }
    case ABY_REFL1:
    {
        AVM_u64 pointer;
        AVM_u32 value;
        AVM_stack_pop(aby->threadv->stack, &value, 4);
        AVM_stack_pop(aby->threadv->stack, &pointer, 8);
        AVM_u8 propvalue = (AVM_u8) value;
        AVM_memory_heapset(pointer, &propvalue, 1);
        break;
    }
    case ABY_REFL2:
    {
        AVM_u64 pointer;
        AVM_u32 value;
        AVM_stack_pop(aby->threadv->stack, &value, 4);
        AVM_stack_pop(aby->threadv->stack, &pointer, 8);
        AVM_u16 propvalue = (AVM_u16) value;
        AVM_memory_heapset(pointer, &propvalue, 2);
        break;
    }
    case ABY_REFL4:
    {
        AVM_u64 pointer;
        AVM_u32 value;
        AVM_stack_pop(aby->threadv->stack, &value, 4);
        AVM_stack_pop(aby->threadv->stack, &pointer, 8);
        AVM_memory_heapset(pointer, &value, 4);
        break;
    }
    case ABY_REFL8:
    {
        AVM_u64 pointer;
        AVM_u64 value;
        AVM_stack_pop(aby->threadv->stack, &value, 8);
        AVM_stack_pop(aby->threadv->stack, &pointer, 8);
        AVM_memory_heapset(pointer, &value, 8);
        break;
    }
    case ABY_EXTR1:
    {
        AVM_u64 pointer;
        AVM_u8 value;
        AVM_stack_pop(aby->threadv->stack, &pointer, 8);
        AVM_memory_heapget(pointer, &value, 1);
        AVM_u32 propvalue = (AVM_u32) value;
        AVM_stack_push(aby->threadv->stack, &propvalue, 4);
        break;
    }
    case ABY_EXTR2:
    {
        AVM_u64 pointer;
        AVM_u16 value;
        AVM_stack_pop(aby->threadv->stack, &pointer, 8);
        AVM_memory_heapget(pointer, &value, 2);
        AVM_u32 propvalue = (AVM_u32) value;
        AVM_stack_push(aby->threadv->stack, &propvalue, 4);
        break;
    }
    case ABY_EXTR4:
    {
        AVM_u64 pointer;
        AVM_u32 value;
        AVM_stack_pop(aby->threadv->stack, &pointer, 8);
        AVM_memory_heapget(pointer, &value, 4);
        AVM_stack_push(aby->threadv->stack, &value, 4);
        break;
    }
    case ABY_EXTR8:
    {
        AVM_u64 pointer;
        AVM_u64 value;
        AVM_stack_pop(aby->threadv->stack, &pointer, 8);
        AVM_memory_heapget(pointer, &value, 8);
        AVM_stack_push(aby->threadv->stack, &value, 8);
        break;
    }
    case ABY_SWAP4:
    {
        AVM_u32 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 4);
        AVM_stack_pop(aby->threadv->stack, &value2, 4);
        AVM_stack_push(aby->threadv->stack, &value1, 4);
        AVM_stack_push(aby->threadv->stack, &value2, 4);
        break;
    }
    case ABY_SWAP8:
    {
        AVM_u64 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 8);
        AVM_stack_pop(aby->threadv->stack, &value2, 8);
        AVM_stack_push(aby->threadv->stack, &value1, 8);
        AVM_stack_push(aby->threadv->stack, &value2, 8);
        break;
    }
    case ABY_SWAP84:
    {
        AVM_u64 value1;
        AVM_u32 value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 8);
        AVM_stack_pop(aby->threadv->stack, &value2, 4);
        AVM_stack_push(aby->threadv->stack, &value1, 8);
        AVM_stack_push(aby->threadv->stack, &value2, 4);
        break;
    }
    case ABY_SWAP48:
    {
        AVM_u32 value1;
        AVM_u64 value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 4);
        AVM_stack_pop(aby->threadv->stack, &value2, 8);
        AVM_stack_push(aby->threadv->stack, &value1, 4);
        AVM_stack_push(aby->threadv->stack, &value2, 8);
        break;
    }
    case ABY_DUP4:
    {
        AVM_u32 value;
        AVM_stack_pop(aby->threadv->stack, &value, 4);
        AVM_stack_push(aby->threadv->stack, &value, 4);
        AVM_stack_push(aby->threadv->stack, &value, 4);
        break;
    }
    case ABY_DUP8:
    {
        AVM_u64 value;
        AVM_stack_pop(aby->threadv->stack, &value, 8);
        AVM_stack_push(aby->threadv->stack, &value, 8);
        AVM_stack_push(aby->threadv->stack, &value, 8);
        break;
    }
    case ABY_ADDI4:
    {
        AVM_i32 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 4);
        AVM_stack_pop(aby->threadv->stack, &value2, 4);
        value1 += value2;
        AVM_stack_push(aby->threadv->stack, &value1, 4);
        break;
    }
    case ABY_ADDI8:
    {
        AVM_i64 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 8);
        AVM_stack_pop(aby->threadv->stack, &value2, 8);
        value1 += value2;
        AVM_stack_push(aby->threadv->stack, &value1, 8);
        break;
    }
    case ABY_ADDF4:
    {
        AVM_f32 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 4);
        AVM_stack_pop(aby->threadv->stack, &value2, 4);
        value1 += value2;
        AVM_stack_push(aby->threadv->stack, &value1, 4);
        break;
    }
    case ABY_ADDF8:
    {
        AVM_f64 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 8);
        AVM_stack_pop(aby->threadv->stack, &value2, 8);
        value1 += value2;
        AVM_stack_push(aby->threadv->stack, &value1, 8);
        break;
    }
    case ABY_SUBI4:
    {
        AVM_i32 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 4);
        AVM_stack_pop(aby->threadv->stack, &value2, 4);
        value1 -= value2;
        AVM_stack_push(aby->threadv->stack, &value1, 4);
        break;
    }
    case ABY_SUBI8:
    {
        AVM_i64 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 8);
        AVM_stack_pop(aby->threadv->stack, &value2, 8);
        value1 -= value2;
        AVM_stack_push(aby->threadv->stack, &value1, 8);
        break;
    }
    case ABY_SUBF4:
    {
        AVM_f32 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 4);
        AVM_stack_pop(aby->threadv->stack, &value2, 4);
        value1 -= value2;
        AVM_stack_push(aby->threadv->stack, &value1, 4);
        break;
    }
    case ABY_SUBF8:
    {
        AVM_f64 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 8);
        AVM_stack_pop(aby->threadv->stack, &value2, 8);
        value1 -= value2;
        AVM_stack_push(aby->threadv->stack, &value1, 8);
        break;
    }
    case ABY_MULI4:
    {
        AVM_i32 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 4);
        AVM_stack_pop(aby->threadv->stack, &value2, 4);
        value1 *= value2;
        AVM_stack_push(aby->threadv->stack, &value1, 4);
        break;
    }
    case ABY_MULI8:
    {
        AVM_i64 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 8);
        AVM_stack_pop(aby->threadv->stack, &value2, 8);
        value1 *= value2;
        AVM_stack_push(aby->threadv->stack, &value1, 8);
        break;
    }
    case ABY_MULF4:
    {
        AVM_f32 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 4);
        AVM_stack_pop(aby->threadv->stack, &value2, 4);
        value1 *= value2;
        AVM_stack_push(aby->threadv->stack, &value1, 4);
        break;
    }
    case ABY_MULF8:
    {
        AVM_f64 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 8);
        AVM_stack_pop(aby->threadv->stack, &value2, 8);
        value1 *= value2;
        AVM_stack_push(aby->threadv->stack, &value1, 8);
        break;
    }
    case ABY_DIVI4:
    {
        AVM_i32 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 4);
        AVM_stack_pop(aby->threadv->stack, &value2, 4);
        value1 /= value2;
        AVM_stack_push(aby->threadv->stack, &value1, 4);
        break;
    }
    case ABY_DIVI8:
    {
        AVM_i64 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 8);
        AVM_stack_pop(aby->threadv->stack, &value2, 8);
        value1 /= value2;
        AVM_stack_push(aby->threadv->stack, &value1, 8);
        break;
    }
    case ABY_DIVU4:
    {
        AVM_u32 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 4);
        AVM_stack_pop(aby->threadv->stack, &value2, 4);
        value1 /= value2;
        AVM_stack_push(aby->threadv->stack, &value1, 4);
        break;
    }
    case ABY_DIVU8:
    {
        AVM_u64 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 8);
        AVM_stack_pop(aby->threadv->stack, &value2, 8);
        value1 /= value2;
        AVM_stack_push(aby->threadv->stack, &value1, 8);
        break;
    }
    case ABY_DIVF4:
    {
        AVM_f32 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 4);
        AVM_stack_pop(aby->threadv->stack, &value2, 4);
        value1 /= value2;
        AVM_stack_push(aby->threadv->stack, &value1, 4);
        break;
    }
    case ABY_DIVF8:
    {
        AVM_f64 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 8);
        AVM_stack_pop(aby->threadv->stack, &value2, 8);
        value1 /= value2;
        AVM_stack_push(aby->threadv->stack, &value1, 8);
        break;
    }
    case ABY_REMI4:
    {
        AVM_i32 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 4);
        AVM_stack_pop(aby->threadv->stack, &value2, 4);
        value1 %= value2;
        AVM_stack_push(aby->threadv->stack, &value1, 4);
        break;
    }
    case ABY_REMI8:
    {
        AVM_i64 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 8);
        AVM_stack_pop(aby->threadv->stack, &value2, 8);
        value1 %= value2;
        AVM_stack_push(aby->threadv->stack, &value1, 8);
        break;
    }
    case ABY_REMU4:
    {
        AVM_u32 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 4);
        AVM_stack_pop(aby->threadv->stack, &value2, 4);
        value1 %= value2;
        AVM_stack_push(aby->threadv->stack, &value1, 4);
        break;
    }
    case ABY_REMU8:
    {
        AVM_u64 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 8);
        AVM_stack_pop(aby->threadv->stack, &value2, 8);
        value1 %= value2;
        AVM_stack_push(aby->threadv->stack, &value1, 8);
        break;
    }
    case ABY_NEGI4:
    {
        AVM_i32 value;
        AVM_stack_pop(aby->threadv->stack, &value, 4);
        value = -value;
        AVM_stack_push(aby->threadv->stack, &value, 4);
        break;
    }
    case ABY_NEGI8:
    {
        AVM_i64 value;
        AVM_stack_pop(aby->threadv->stack, &value, 8);
        value = -value;
        AVM_stack_push(aby->threadv->stack, &value, 8);
        break;
    }
    case ABY_NEGF4:
    {
        AVM_f32 value;
        AVM_stack_pop(aby->threadv->stack, &value, 4);
        value = -value;
        AVM_stack_push(aby->threadv->stack, &value, 4);
        break;
    }
    case ABY_NEGF8:
    {
        AVM_f64 value;
        AVM_stack_pop(aby->threadv->stack, &value, 8);
        value = -value;
        AVM_stack_push(aby->threadv->stack, &value, 8);
        break;
    }
    case ABY_SHL4:
    {
        AVM_u32 value;
        AVM_u32 shiftam;
        AVM_stack_pop(aby->threadv->stack, &shiftam, 4);
        AVM_stack_pop(aby->threadv->stack, &value, 4);
        value <<= shiftam;
        AVM_stack_push(aby->threadv->stack, &value, 4);
        break;
    }
    case ABY_SHL8:
    {
        AVM_u64 value;
        AVM_u32 shiftam;
        AVM_stack_pop(aby->threadv->stack, &shiftam, 4);
        AVM_stack_pop(aby->threadv->stack, &value, 8);
        value <<= shiftam;
        AVM_stack_push(aby->threadv->stack, &value, 8);
        break;
    }
    case ABY_SHR4:
    {
        AVM_i32 value;
        AVM_u32 shiftam;
        AVM_stack_pop(aby->threadv->stack, &shiftam, 4);
        AVM_stack_pop(aby->threadv->stack, &value, 4);
        value >>= shiftam;  // implementation defined behavior
        AVM_stack_push(aby->threadv->stack, &value, 4);
        break;
    }
    case ABY_SHR8:
    {
        AVM_i64 value;
        AVM_u32 shiftam;
        AVM_stack_pop(aby->threadv->stack, &shiftam, 4);
        AVM_stack_pop(aby->threadv->stack, &value, 8);
        value >>= shiftam;  // implementation defined behavior
        AVM_stack_push(aby->threadv->stack, &value, 8);
        break;
    }
    case ABY_SHRU4:
    {
        AVM_u32 value;
        AVM_u32 shiftam;
        AVM_stack_pop(aby->threadv->stack, &shiftam, 4);
        AVM_stack_pop(aby->threadv->stack, &value, 4);
        value >>= shiftam;
        AVM_stack_push(aby->threadv->stack, &value, 4);
        break;
    }
    case ABY_SHRU8:
    {
        AVM_u64 value;
        AVM_u32 shiftam;
        AVM_stack_pop(aby->threadv->stack, &shiftam, 4);
        AVM_stack_pop(aby->threadv->stack, &value, 8);
        value >>= shiftam;
        AVM_stack_push(aby->threadv->stack, &value, 8);
        break;
    }
    case ABY_BNOT4:
    {
        AVM_u32 value;
        AVM_stack_pop(aby->threadv->stack, &value, 4);
        value = ~value;
        AVM_stack_push(aby->threadv->stack, &value, 4);
        break;
    }
    case ABY_BNOT8:
    {
        AVM_u64 value;
        AVM_stack_pop(aby->threadv->stack, &value, 8);
        value = ~value;
        AVM_stack_push(aby->threadv->stack, &value, 8);
        break;
    }
    case ABY_BAND4:
    {
        AVM_u32 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 4);
        AVM_stack_pop(aby->threadv->stack, &value2, 4);
        value1 &= value2;
        AVM_stack_push(aby->threadv->stack, &value1, 4);
        break;
    }
    case ABY_BAND8:
    {
        AVM_u64 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 8);
        AVM_stack_pop(aby->threadv->stack, &value2, 8);
        value1 &= value2;
        AVM_stack_push(aby->threadv->stack, &value1, 8);
        break;
    }
    case ABY_BXOR4:
    {
        AVM_u32 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 4);
        AVM_stack_pop(aby->threadv->stack, &value2, 4);
        value1 ^= value2;
        AVM_stack_push(aby->threadv->stack, &value1, 4);
        break;
    }
    case ABY_BXOR8:
    {
        AVM_u64 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 8);
        AVM_stack_pop(aby->threadv->stack, &value2, 8);
        value1 ^= value2;
        AVM_stack_push(aby->threadv->stack, &value1, 8);
        break;
    }
    case ABY_BOR4:
    {
        AVM_u32 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 4);
        AVM_stack_pop(aby->threadv->stack, &value2, 4);
        value1 |= value2;
        AVM_stack_push(aby->threadv->stack, &value1, 4);
        break;
    }
    case ABY_BOR8:
    {
        AVM_u64 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 8);
        AVM_stack_pop(aby->threadv->stack, &value2, 8);
        value1 |= value2;
        AVM_stack_push(aby->threadv->stack, &value1, 8);
        break;
    }
    case ABY_LNOT4:
    {
        AVM_u32 value;
        AVM_stack_pop(aby->threadv->stack, &value, 4);
        AVM_u32 result = !value;
        AVM_stack_push(aby->threadv->stack, &result, 4);
        break;
    }
    case ABY_LNOT8:
    {
        AVM_u64 value;
        AVM_stack_pop(aby->threadv->stack, &value, 8);
        value = !value;
        AVM_stack_push(aby->threadv->stack, &value, 8);
        break;
    }
    case ABY_LAND4:
    {
        AVM_u32 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 4);
        AVM_stack_pop(aby->threadv->stack, &value2, 4);
        value1 = value1 && value2;
        AVM_stack_push(aby->threadv->stack, &value1, 4);
        break;
    }
    case ABY_LAND8:
    {
        AVM_u64 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 8);
        AVM_stack_pop(aby->threadv->stack, &value2, 8);
        value1 = value1 && value2;
        AVM_stack_push(aby->threadv->stack, &value1, 8);
        break;
    }
    case ABY_LOR4:
    {
        AVM_u32 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 4);
        AVM_stack_pop(aby->threadv->stack, &value2, 4);
        value1 = value1 || value2;
        AVM_stack_push(aby->threadv->stack, &value1, 4);
        break;
    }
    case ABY_LOR8:
    {
        AVM_u64 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 8);
        AVM_stack_pop(aby->threadv->stack, &value2, 8);
        value1 = value1 || value2;
        AVM_stack_push(aby->threadv->stack, &value1, 8);
        break;
    }
    case ABY_CI14:
    {
        AVM_i32 i8val;
        AVM_stack_pop(aby->threadv->stack, &i8val, 4);
        AVM_i32 i32val = (AVM_i8) i8val;
        AVM_stack_push(aby->threadv->stack, &i32val, 4);
        break;
    }
    case ABY_CI24:
    {
        AVM_i32 i16val;
        AVM_stack_pop(aby->threadv->stack, &i16val, 4);
        AVM_i32 i32val = (AVM_i16) i16val;
        AVM_stack_push(aby->threadv->stack, &i32val, 4);
        break;
    }
    case ABY_CI41:
    {
        AVM_i32 i32val;
        AVM_stack_pop(aby->threadv->stack, &i32val, 4);
        AVM_i32 i8val = (AVM_i8) i32val;
        AVM_stack_push(aby->threadv->stack, &i8val, 4);
        break;
    }
    case ABY_CI42:
    {
        AVM_i32 i32val;
        AVM_stack_pop(aby->threadv->stack, &i32val, 4);
        AVM_i32 i16val = (AVM_i32) i32val;
        AVM_stack_push(aby->threadv->stack, &i16val, 4);
        break;
    }
    case ABY_CI48:
    {
        AVM_i32 i32val;
        AVM_stack_pop(aby->threadv->stack, &i32val, 4);
        AVM_i64 i64val = (AVM_i64) i32val;
        AVM_stack_push(aby->threadv->stack, &i64val, 8);
        break;
    }
    case ABY_CI84:
    {
        AVM_i64 i64val;
        AVM_stack_pop(aby->threadv->stack, &i64val, 8);
        AVM_i32 i32val = (AVM_i32) i64val;
        AVM_stack_push(aby->threadv->stack, &i32val, 4);
        break;
    }
    case ABY_CF48:
    {
        AVM_f32 f32val;
        AVM_stack_pop(aby->threadv->stack, &f32val, 4);
        AVM_f64 f64val = (AVM_f64) f32val;
        AVM_stack_push(aby->threadv->stack, &f64val, 8);
        break;
    }
    case ABY_CF84:
    {
        AVM_f64 f64val;
        AVM_stack_pop(aby->threadv->stack, &f64val, 8);
        AVM_f32 f32val = (AVM_f32) f64val;
        AVM_stack_push(aby->threadv->stack, &f32val, 4);
        break;
    }
    case ABY_CFI4:
    {
        AVM_f32 f32val;
        AVM_stack_pop(aby->threadv->stack, &f32val, 4);
        AVM_i32 i32val = (AVM_i32) f32val;
        AVM_stack_push(aby->threadv->stack, &i32val, 4);
        break;
    }
    case ABY_CFI8:
    {
        AVM_f64 f64val;
        AVM_stack_pop(aby->threadv->stack, &f64val, 8);
        AVM_i64 i64val = (AVM_i64) f64val;
        AVM_stack_push(aby->threadv->stack, &i64val, 8);
        break;
    }
    case ABY_CIF4:
    {
        AVM_f32 i32val;
        AVM_stack_pop(aby->threadv->stack, &i32val, 4);
        AVM_i32 f32val = (AVM_f32) i32val;
        AVM_stack_push(aby->threadv->stack, &f32val, 4);
        break;
    }
    case ABY_CIF8:
    {
        AVM_i64 i64val;
        AVM_stack_pop(aby->threadv->stack, &i64val, 8);
        AVM_f64 f64val = (AVM_f64) i64val;
        AVM_stack_push(aby->threadv->stack, &f64val, 8);
        break;
    }
    case ABY_GOTO:
    {
        AVM_u32 pc;
        AVM_bytecode_next(aby->threadv->bcode, &aby->threadv->pc, &pc, 4);
        aby->threadv->pc = aby->threadv->bcode->bcb + pc;
        break;
    }
    case ABY_CALL:
    {
        AVM_u32 function;
        AVM_bytecode_next(aby->threadv->bcode, &aby->threadv->pc, &function, 4);
        AVM_thread_push(aby->threadv, aby->bcodev[function]);
        break;
    }
    case ABY_RETURN:
    {
        AVM_thread_pop(aby->threadv);
        break;
    }
    case ABY_NATIVE:
    {
        AVM_u32 native;
        AVM_bytecode_next(aby->threadv->bcode, &aby->threadv->pc, &native, 4);
        aby->nativev[native]->cfunc(aby);
        break;
    }
    case ABY_IF:
    {
        AVM_u32 pc, value;
        AVM_stack_pop(aby->threadv->stack, &value, 4);
        AVM_bytecode_next(aby->threadv->bcode, &aby->threadv->pc, &pc, 4);
        if(value) aby->threadv->pc = aby->threadv->bcode->bcb + pc;
        break;
    }
    case ABY_IFN:
    {
        AVM_u32 pc, value;
        AVM_stack_pop(aby->threadv->stack, &value, 4);
        AVM_bytecode_next(aby->threadv->bcode, &aby->threadv->pc, &pc, 4);
        if(!value) aby->threadv->pc = aby->threadv->bcode->bcb + pc;
        break;
    }
    case ABY_LTNL:
    {
        AVM_i32 value;
        AVM_stack_pop(aby->threadv->stack, &value, 4);
        AVM_i32 result = value < 0;
        AVM_stack_push(aby->threadv->stack, &result, 4);
        break;
    }
    case ABY_LENL:
    {
        AVM_i32 value;
        AVM_stack_pop(aby->threadv->stack, &value, 4);
        AVM_i32 result = value <= 0;
        AVM_stack_push(aby->threadv->stack, &result, 4);
        break;
    }
    case ABY_GTNL:
    {
        AVM_i32 value;
        AVM_stack_pop(aby->threadv->stack, &value, 4);
        AVM_i32 result = value > 0;
        AVM_stack_push(aby->threadv->stack, &result, 4);
        break;
    }
    case ABY_GENL:
    {
        AVM_i32 value;
        AVM_stack_pop(aby->threadv->stack, &value, 4);
        AVM_i32 result = value >= 0;
        AVM_stack_push(aby->threadv->stack, &result, 4);
        break;
    }
    case ABY_EQNL:
    {
        AVM_i32 value;
        AVM_stack_pop(aby->threadv->stack, &value, 4);
        AVM_i32 result = value == 0;
        AVM_stack_push(aby->threadv->stack, &result, 4);
        break;
    }
    case ABY_NENL:
    {
        AVM_i32 value;
        AVM_stack_pop(aby->threadv->stack, &value, 4);
        AVM_i32 result = value != 0;
        AVM_stack_push(aby->threadv->stack, &result, 4);
        break;
    }
    case ABY_CMP4:
    {
        AVM_u32 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value2, 4);
        AVM_stack_pop(aby->threadv->stack, &value1, 4);
        AVM_i32 result = 0;
        if(value1 < value2) result = -1;
        else if(value1 > value2) result = 1;
        AVM_stack_push(aby->threadv->stack, &result, 4);
        break;
    }
    case ABY_CMP8:
    {
        AVM_u64 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value2, 8);
        AVM_stack_pop(aby->threadv->stack, &value1, 8);
        AVM_i32 result = 0;
        if(value1 < value2) result = -1;
        else if(value1 > value2) result = 1;
        AVM_stack_push(aby->threadv->stack, &result, 4);
        break;
    }
    case ABY_ICMP4:
    {
        AVM_i32 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value2, 4);
        AVM_stack_pop(aby->threadv->stack, &value1, 4);
        AVM_i32 result = 0;
        if(value1 < value2) result = -1;
        else if(value1 > value2) result = 1;
        AVM_stack_push(aby->threadv->stack, &result, 4);
        break;
    }
    case ABY_ICMP8:
    {
        AVM_i64 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value2, 8);
        AVM_stack_pop(aby->threadv->stack, &value1, 8);
        AVM_i32 result = 0;
        if(value1 < value2) result = -1;
        else if(value1 > value2) result = 1;
        AVM_stack_push(aby->threadv->stack, &result, 4);
        break;
    }
    case ABY_IUCMP4:
    {
        AVM_i32 value1;
        AVM_u32 value2;
        AVM_stack_pop(aby->threadv->stack, &value2, 4);
        AVM_stack_pop(aby->threadv->stack, &value1, 4);
        AVM_i32 result = 0;
        if(value1 < 0 || (AVM_u32) value1 < value2) result = -1;
        else if((AVM_u32) value1 > value2) result = 1;
        AVM_stack_push(aby->threadv->stack, &result, 4);
        break;
    }
    case ABY_IUCMP8:
    {
        AVM_i64 value1;
        AVM_u64 value2;
        AVM_stack_pop(aby->threadv->stack, &value2, 8);
        AVM_stack_pop(aby->threadv->stack, &value1, 8);
        AVM_i32 result = 0;
        if(value1 < 0 || (AVM_u64) value1 < value2) result = -1;
        else if((AVM_u64) value1 > value2) result = 1;
        AVM_stack_push(aby->threadv->stack, &result, 4);
        break;
    }
    case ABY_IUCMPR4:
    {
        AVM_i32 value1;
        AVM_u32 value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 4);
        AVM_stack_pop(aby->threadv->stack, &value2, 4);
        AVM_i32 result = 0;
        if(value1 < 0 || (AVM_u32) value1 < value2) result = -1;
        else if((AVM_u32) value1 > value2) result = 1;
        AVM_stack_push(aby->threadv->stack, &result, 4);
        break;
    }
    case ABY_IUCMPR8:
    {
        AVM_i64 value1;
        AVM_u64 value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 8);
        AVM_stack_pop(aby->threadv->stack, &value2, 8);
        AVM_i32 result = 0;
        if(value1 < 0 || (AVM_u64) value1 < value2) result = -1;
        else if((AVM_u64) value1 > value2) result = 1;
        AVM_stack_push(aby->threadv->stack, &result, 4);
        break;
    }
    case ABY_FCMP4:
    {
        AVM_f32 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value2, 4);
        AVM_stack_pop(aby->threadv->stack, &value1, 4);
        AVM_i32 result = 0;
        if(value1 < value2) result = -1;
        else if(value1 > value2) result = 1;
        AVM_stack_push(aby->threadv->stack, &result, 4);
        break;
    }
    case ABY_FCMP8:
    {
        AVM_f32 value1, value2;
        AVM_stack_pop(aby->threadv->stack, &value2, 8);
        AVM_stack_pop(aby->threadv->stack, &value1, 8);
        AVM_i32 result = 0;
        if(value1 < value2) result = -1;
        else if(value1 > value2) result = 1;
        AVM_stack_push(aby->threadv->stack, &result, 4);
        break;
    }
    case ABY_FICMP4:
    {
        AVM_f32 value1;
        AVM_i32 value2;
        AVM_stack_pop(aby->threadv->stack, &value2, 4);
        AVM_stack_pop(aby->threadv->stack, &value1, 4);
        AVM_i32 result = 0;
        if(value1 < value2) result = -1;
        else if(value1 > value2) result = 1;
        AVM_stack_push(aby->threadv->stack, &result, 4);
        break;
    }
    case ABY_FICMP8:
    {
        AVM_f64 value1;
        AVM_i64 value2;
        AVM_stack_pop(aby->threadv->stack, &value2, 8);
        AVM_stack_pop(aby->threadv->stack, &value1, 8);
        AVM_i32 result = 0;
        if(value1 < value2) result = -1;
        else if(value1 > value2) result = 1;
        AVM_stack_push(aby->threadv->stack, &result, 4);
        break;
    }
    case ABY_FICMPR4:
    {
        AVM_f32 value1;
        AVM_i32 value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 4);
        AVM_stack_pop(aby->threadv->stack, &value2, 4);
        AVM_i32 result = 0;
        if(value1 < value2) result = -1;
        else if(value1 > value2) result = 1;
        AVM_stack_push(aby->threadv->stack, &result, 4);
        break;
    }
    case ABY_FICMPR8:
    {
        AVM_f64 value1;
        AVM_i64 value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 8);
        AVM_stack_pop(aby->threadv->stack, &value2, 8);
        AVM_i32 result = 0;
        if(value1 < value2) result = -1;
        else if(value1 > value2) result = 1;
        AVM_stack_push(aby->threadv->stack, &result, 4);
        break;
    }
    case ABY_FUCMP4:
    {
        AVM_f32 value1;
        AVM_u32 value2;
        AVM_stack_pop(aby->threadv->stack, &value2, 4);
        AVM_stack_pop(aby->threadv->stack, &value1, 4);
        AVM_i32 result = 0;
        if(value1 < 0.0f || value1 < value2) result = -1;
        else if(value1 > value2) result = 1;
        AVM_stack_push(aby->threadv->stack, &result, 4);
        break;
    }
    case ABY_FUCMP8:
    {
        AVM_f64 value1;
        AVM_u64 value2;
        AVM_stack_pop(aby->threadv->stack, &value2, 8);
        AVM_stack_pop(aby->threadv->stack, &value1, 8);
        AVM_i32 result = 0;
        if(value1 < 0.0 || value1 < value2) result = -1;
        else if(value1 > value2) result = 1;
        AVM_stack_push(aby->threadv->stack, &result, 4);
        break;
    }
    case ABY_FUCMPR4:
    {
        AVM_f32 value1;
        AVM_u32 value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 4);
        AVM_stack_pop(aby->threadv->stack, &value2, 4);
        AVM_i32 result = 0;
        if(value1 < 0.0f || value1 < value2) result = -1;
        else if(value1 > value2) result = 1;
        AVM_stack_push(aby->threadv->stack, &result, 4);
        break;
    }
    case ABY_FUCMPR8:
    {
        AVM_f64 value1;
        AVM_u64 value2;
        AVM_stack_pop(aby->threadv->stack, &value1, 8);
        AVM_stack_pop(aby->threadv->stack, &value2, 8);
        AVM_i32 result = 0;
        if(value1 < 0.0 || value1 < value2) result = -1;
        else if(value1 > value2) result = 1;
        AVM_stack_push(aby->threadv->stack, &result, 4);
        break;
    }
    default:
        AVM_abort("unrecognized opcode", AVM_ERRNO_UNREGOPC);
    }
}
