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
        break;
    }
    case ABY_PUSH8:
    {
        break;
    }
    case ABY_POP4:
    {
        break;
    }
    case ABY_POP8:
    {
        break;
    }
    case ABY_LOAD4:
    {
        break;
    }
    case ABY_LOAD8:
    {
        break;
    }
    case ABY_FETCH4:
    {
        break;
    }
    case ABY_FETCH8:
    {
        break;
    }
    case ABY_LOADWIDE4:
    {
        break;
    }
    case ABY_LOADWIDE8:
    {
        break;
    }
    case ABY_FETCHWIDE4:
    {
        break;
    }
    case ABY_FETCHWIDE8:
    {
        break;
    }
    case ABY_ALLOC:
    {
        break;
    }
    case ABY_FREE:
    {
        break;
    }
    case ABY_REFL1:
    {
        break;
    }
    case ABY_REFL2:
    {
        break;
    }
    case ABY_REFL4:
    {
        break;
    }
    case ABY_REFL8:
    {
        break;
    }
    case ABY_EXTR1:
    {
        break;
    }
    case ABY_EXTR2:
    {
        break;
    }
    case ABY_EXTR4:
    {
        break;
    }
    case ABY_EXTR8:
    {
        break;
    }
    case ABY_SWAP4:
    {
        break;
    }
    case ABY_SWAP8:
    {
        break;
    }
    case ABY_SWAP84:
    {
        break;
    }
    case ABY_SWAP48:
    {
        break;
    }
    case ABY_DUP4:
    {
        break;
    }
    case ABY_DUP8:
    {
        break;
    }
    case ABY_ADDI4:
    {
        break;
    }
    case ABY_ADDI8:
    {
        break;
    }
    case ABY_ADDF4:
    {
        break;
    }
    case ABY_ADDF8:
    {
        break;
    }
    case ABY_SUBI4:
    {
        break;
    }
    case ABY_SUBI8:
    {
        break;
    }
    case ABY_SUBF4:
    {
        break;
    }
    case ABY_SUBF8:
    {
        break;
    }
    case ABY_MULI4:
    {
        break;
    }
    case ABY_MULI8:
    {
        break;
    }
    case ABY_MULF4:
    {
        break;
    }
    case ABY_MULF8:
    {
        break;
    }
    case ABY_DIVI4:
    {
        break;
    }
    case ABY_DIVI8:
    {
        break;
    }
    case ABY_DIVU4:
    {
        break;
    }
    case ABY_DIVU8:
    {
        break;
    }
    case ABY_DIVF4:
    {
        break;
    }
    case ABY_DIVF8:
    {
        break;
    }
    case ABY_REMI4:
    {
        break;
    }
    case ABY_REMI8:
    {
        break;
    }
    case ABY_REMU4:
    {
        break;
    }
    case ABY_REMU8:
    {
        break;
    }
    case ABY_NEGI4:
    {
        break;
    }
    case ABY_NEGI8:
    {
        break;
    }
    case ABY_NEGF4:
    {
        break;
    }
    case ABY_NEGF8:
    {
        break;
    }
    case ABY_SHL4:
    {
        break;
    }
    case ABY_SHL8:
    {
        break;
    }
    case ABY_SHR4:
    {
        break;
    }
    case ABY_SHR8:
    {
        break;
    }
    case ABY_SHRU4:
    {
        break;
    }
    case ABY_SHRU8:
    {
        break;
    }
    case ABY_BNOT4:
    {
        break;
    }
    case ABY_BNOT8:
    {
        break;
    }
    case ABY_BAND4:
    {
        break;
    }
    case ABY_BAND8:
    {
        break;
    }
    case ABY_BXOR4:
    {
        break;
    }
    case ABY_BXOR8:
    {
        break;
    }
    case ABY_BOR4:
    {
        break;
    }
    case ABY_BOR8:
    {
        break;
    }
    case ABY_LNOT4:
    {
        break;
    }
    case ABY_LNOT8:
    {
        break;
    }
    case ABY_LAND4:
    {
        break;
    }
    case ABY_LAND8:
    {
        break;
    }
    case ABY_LOR4:
    {
        break;
    }
    case ABY_LOR8:
    {
        break;
    }
    case ABY_CI14:
    {
        break;
    }
    case ABY_CI24:
    {
        break;
    }
    case ABY_CI41:
    {
        break;
    }
    case ABY_CI42:
    {
        break;
    }
    case ABY_CI48:
    {
        break;
    }
    case ABY_CI84:
    {
        break;
    }
    case ABY_CF48:
    {
        break;
    }
    case ABY_CF84:
    {
        break;
    }
    case ABY_CFI4:
    {
        break;
    }
    case ABY_CFI8:
    {
        break;
    }
    case ABY_CIF4:
    {
        break;
    }
    case ABY_CIF8:
    {
        break;
    }
    case ABY_GOTO:
    {
        break;
    }
    case ABY_IF:
    {
        break;
    }
    case ABY_IFN:
    {
        break;
    }
    case ABY_LTNL:
    {
        break;
    }
    case ABY_LENL:
    {
        break;
    }
    case ABY_GTNL:
    {
        break;
    }
    case ABY_GENL:
    {
        break;
    }
    case ABY_EQNL:
    {
        break;
    }
    case ABY_NENL:
    {
        break;
    }
    case ABY_CMP4:
    {
        break;
    }
    case ABY_CMP8:
    {
        break;
    }
    case ABY_ICMP4:
    {
        break;
    }
    case ABY_ICMP8:
    {
        break;
    }
    case ABY_IUCMP4:
    {
        break;
    }
    case ABY_IUCMP8:
    {
        break;
    }
    case ABY_IUCMPR4:
    {
        break;
    }
    case ABY_IUCMPR8:
    {
        break;
    }
    case ABY_FCMP4:
    {
        break;
    }
    case ABY_FCMP8:
    {
        break;
    }
    case ABY_FICMP4:
    {
        break;
    }
    case ABY_FICMP8:
    {
        break;
    }
    case ABY_FICMPR4:
    {
        break;
    }
    case ABY_FICMPR8:
    {
        break;
    }
    case ABY_FUCMP4:
    {
        break;
    }
    case ABY_FUCMP8:
    {
        break;
    }
    case ABY_FUCMPR4:
    {
        break;
    }
    case ABY_FUCMPR8:
    {
        break;
    }
    case ABY_CALL:
    {
        break;
    }
    case ABY_RETURN:
    {
        break;
    }
    }
}
