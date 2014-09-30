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
 * File: exec.h
 * Description: 
 * Author: Lovro Kalinovcic
 * 
 */

#ifndef EXEC_H_
#define EXEC_H_

#include "aby.h"
#include "atype.h"
#include "bytecode.h"
#include "stack.h"

#define ABY_DEBUGOUT     1

#define ABY_NOP          0x00
#define ABY_PUSH4        0x08
#define ABY_PUSH8        0x09
#define ABY_POP4         0x0C
#define ABY_POP8         0x0D

#define ABY_LOAD4        0x10
#define ABY_LOAD8        0x11
#define ABY_LOADWIDE4    0x12
#define ABY_LOADWIDE8    0x13
#define ABY_FETCH4       0x18
#define ABY_FETCH8       0x19
#define ABY_FETCHWIDE4   0x1A
#define ABY_FETCHWIDE8   0x1B

#define ABY_ALLOC        0x20
#define ABY_FREE         0x21

#define ABY_REFL1        0x30
#define ABY_REFL2        0x31
#define ABY_REFL4        0x32
#define ABY_REFL8        0x33
#define ABY_EXTR1        0x38
#define ABY_EXTR2        0x39
#define ABY_EXTR4        0x3A
#define ABY_EXTR8        0x3B

#define ABY_SWAP4        0x40
#define ABY_SWAP8        0x41
#define ABY_SWAP48       0x42
#define ABY_SWAP84       0x43
#define ABY_DUP4         0x48
#define ABY_DUP8         0x49

#define ABY_ADDI4        0x50
#define ABY_ADDI8        0x51
#define ABY_ADDF4        0x52
#define ABY_ADDF8        0x53
#define ABY_SUBI4        0x54
#define ABY_SUBI8        0x55
#define ABY_SUBF4        0x56
#define ABY_SUBF8        0x57
#define ABY_MULI4        0x58
#define ABY_MULI8        0x59
#define ABY_MULF4        0x5A
#define ABY_MULF8        0x5B
#define ABY_DIVI4        0x5C
#define ABY_DIVI8        0x5D
#define ABY_DIVU4        0x5E
#define ABY_DIVU8        0x5F
#define ABY_DIVF4        0x60
#define ABY_DIVF8        0x61
#define ABY_REMI4        0x62
#define ABY_REMI8        0x63
#define ABY_REMU4        0x64
#define ABY_REMU8        0x65
#define ABY_NEGI4        0x66
#define ABY_NEGI8        0x67
#define ABY_NEGF4        0x68
#define ABY_NEGF8        0x69

#define ABY_SHL4         0x80
#define ABY_SHL8         0x81
#define ABY_SHR4         0x82
#define ABY_SHR8         0x83
#define ABY_SHRU4        0x84
#define ABY_SHRU8        0x85
#define ABY_BNOT4        0x86
#define ABY_BNOT8        0x87
#define ABY_BAND4        0x88
#define ABY_BAND8        0x89
#define ABY_BXOR4        0x8A
#define ABY_BXOR8        0x8B
#define ABY_BOR4         0x8C
#define ABY_BOR8         0x8D

#define ABY_LNOT4        0xA0
#define ABY_LNOT8        0xA1
#define ABY_LAND4        0xA2
#define ABY_LAND8        0xA3
#define ABY_LOR4         0xA4
#define ABY_LOR8         0xA5

#define ABY_CI14         0xB0
#define ABY_CI24         0xB1
#define ABY_CI41         0xB2
#define ABY_CI42         0xB3
#define ABY_CI48         0xB4
#define ABY_CI84         0xB5
#define ABY_CF48         0xB6
#define ABY_CF84         0xB7
#define ABY_CFI4         0xB8
#define ABY_CFI8         0xB9
#define ABY_CIF4         0xBA
#define ABY_CIF8         0xBB

#define ABY_GOTO         0xD0
#define ABY_CALL         0xD1
#define ABY_RETURN       0xD2
#define ABY_IF           0xD4
#define ABY_IFN          0xD5
#define ABY_LTNL         0xDA
#define ABY_LENL         0xDB
#define ABY_GTNL         0xDC
#define ABY_GENL         0xDD
#define ABY_EQNL         0xDE
#define ABY_NENL         0xDF

#define ABY_CMP4         0xE0
#define ABY_CMP8         0xE1
#define ABY_ICMP4        0xE2
#define ABY_ICMP8        0xE3
#define ABY_IUCMP4       0xE4
#define ABY_IUCMP8       0xE5
#define ABY_IUCMPR4      0xE6
#define ABY_IUCMPR8      0xE7
#define ABY_FCMP4        0xE8
#define ABY_FCMP8        0xE9
#define ABY_FICMP4       0xEA
#define ABY_FICMP8       0xEB
#define ABY_FICMPR4      0xEC
#define ABY_FICMPR8      0xED
#define ABY_FUCMP4       0xEE
#define ABY_FUCMP8       0xEF
#define ABY_FUCMPR4      0xF1
#define ABY_FUCMPR8      0xF2

void AVM_ABYexecutor_nextrun(struct AVM_ABY* aby);

#endif /* EXEC_H_ */
