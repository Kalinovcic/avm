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
 * File: error.h
 * Description: 
 * Author: Lovro Kalinovcic
 * 
 */

#ifndef ERROR_H_
#define ERROR_H_

#include <stdlib.h>
#include <stdio.h>

#include "atype.h"

#define AVM_ERRNO_ABYFLOAD      0x0F0F0F0F
#define AVM_ERRNO_ABYINVHD      0xFF0F0FF0
#define AVM_ERRNO_OUTOFMEM      0xF0F0F0F0
#define AVM_ERRNO_SEGMNFLT      0xFF00FF00
#define AVM_ERRNO_OVERFLOW      0xFFFF0000
#define AVM_ERRNO_UNDRFLOW      0xFFFF0010
#define AVM_ERRNO_BCODLOAD      0xFFFF0100
#define AVM_ERRNO_BCODEEOF      0xFFFF0110
#define AVM_ERRNO_BCINVLPC      0xFFFF0120

void AVM_abort(char* msg, AVM_u32 errno);

#endif /* ERROR_H_ */
