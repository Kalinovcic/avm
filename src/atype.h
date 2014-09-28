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

typedef int8_t   AVM_i8;
typedef int16_t  AVM_i16;
typedef int32_t  AVM_i32;
typedef int64_t  AVM_i64;

typedef uint8_t  AVM_u8;
typedef uint16_t AVM_u16;
typedef uint32_t AVM_u32;
typedef uint64_t AVM_u64;

typedef float    AVM_f32;
typedef double   AVM_f64;

typedef AVM_u64  AVM_size;

#define AVM_TRUE       -1
#define AVM_FALSE       0

typedef int      AVM_bool;

#endif /* ATYPE_H_ */
