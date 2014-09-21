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
 * File: atype.h
 * Description: 
 * Author: Lovro Kalinovcic
 * 
 */

#ifndef ATYPE_H_
#define ATYPE_H_

#include <stdint.h>

typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float    f32;
typedef double   f64;

typedef u32      asize;

#define ECINVCLEAR             0xFFCB0000
#define ECINVLOAD              0xFFCB0001
#define ECINVMOV               0xFFCB0002
#define ECLAPMOV               0xFFCB0003
#define ECINVSWAP              0xFFCB0004
#define ECLAPSWAP              0xFFCB0005
#define ECINVINC               0xFFCB0006
#define ECINVDEC               0xFFCB0007
#define ECINVNEG               0xFFCB0008
#define ECINVADD               0xFFCB0009
#define ECINVSUB               0xFFCB000A
#define ECINVMUL               0xFFCB000B
#define ECINVDIV               0xFFCB000C
#define ECINVIDIV              0xFFCB000D
#define ECINVFADD              0xFFCB000E
#define ECINVFIADD             0xFFCB000F
#define ECINVFUADD             0xFFCB0010
#define ECINVFSUB              0xFFCB0011
#define ECINVFISUB             0xFFCB0012
#define ECINVFISUBR            0xFFCB0013
#define ECINVFUSUB             0xFFCB0014
#define ECINVFUSUBR            0xFFCB0015
#define ECINVFMUL              0xFFCB0016
#define ECINVFIMUL             0xFFCB0017
#define ECINVFUMUL             0xFFCB0018
#define ECINVFDIV              0xFFCB0019
#define ECINVFIDIV             0xFFCB001A
#define ECINVFIDIVR            0xFFCB001B
#define ECINVFUDIV             0xFFCB001C
#define ECINVFUDIVR            0xFFCB001D
#define ECINVFNEG              0xFFCB001E
#define ECINVROT               0xFFCB001F
#define ECINVSHTL              0xFFCB0020
#define ECINVSHTR              0xFFCB0021
#define ECINVBAND              0xFFCB0022
#define ECINVBOR               0xFFCB0023
#define ECINVBXOR              0xFFCB0024
#define ECINVBNOT              0xFFCB0025

#endif /* ATYPE_H_ */
