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

#define AVM_MASK_FATAL              (0xE1000000)

#define AVM_MASK_LOAD               (0x00620000)      // error caused by VM loading an invalid resource
#define AVM_MASK_CODE               (0x00930000)      // error caused by invalid code, not by VM malfunction
#define AVM_MASK_MEMORY             (0x00C70000)      // error caused by memory bugs
#define AVM_MASK_LINK               (0x00E60000)      // error caused during linking

#define AVM_MASK_STACK              (0x00001300)      // error is related to the stack
#define AVM_MASK_NATIVE             (0x00002300)      // error is related to native functions
#define AVM_MASK_ABY                (0x00006200)      // error is related to the ABY system
#define AVM_MASK_BCODE              (0x0000A600)      // error is related to byte code
#define AVM_MASK_HEAP               (0x0000B700)      // error is related to heap memory
#define AVM_MASK_GLOBALMEM          (0x0000E800)      // error is related to global memory
#define AVM_MASK_LOCALMEM           (0x0000F700)      // error is related to local memory

#define AVM_ERRNO_ABYFLOAD      ((AVM_MASK_FATAL     | AVM_MASK_LOAD     | AVM_MASK_ABY      ) + 0x00)     // failed to load ABY (usually unexpected EOF)
#define AVM_ERRNO_ABYINVHD      ((AVM_MASK_FATAL     | AVM_MASK_LOAD     | AVM_MASK_ABY      ) + 0x10)     // invalid ABY header
#define AVM_ERRNO_BCODLOAD      ((AVM_MASK_FATAL     | AVM_MASK_LOAD     | AVM_MASK_BCODE    ) + 0x00)     // failed to load byte code
#define AVM_ERRNO_NATLIBNF      ((AVM_MASK_FATAL     | AVM_MASK_LOAD     | AVM_MASK_NATIVE   ) + 0x00)     // native library not found
#define AVM_ERRNO_NLIBOPEN      ((AVM_MASK_FATAL     | AVM_MASK_LOAD     | AVM_MASK_NATIVE   ) + 0x10)     // failed to open native library
#define AVM_ERRNO_NLIBCLSE      ((AVM_MASK_FATAL     | AVM_MASK_LOAD     | AVM_MASK_NATIVE   ) + 0x20)     // failed to close native library
#define AVM_ERRNO_NLIBLFUN      ((AVM_MASK_FATAL     | AVM_MASK_LOAD     | AVM_MASK_NATIVE   ) + 0x30)     // failed to load native function from a native library
#define AVM_ERRNO_DUPNTSYM      ((AVM_MASK_FATAL     | AVM_MASK_LINK     | AVM_MASK_NATIVE   ) + 0x30)     // duplicate native function
#define AVM_ERRNO_NATSYMNF      ((AVM_MASK_FATAL     | AVM_MASK_LINK     | AVM_MASK_NATIVE   ) + 0x30)     // native function not found
#define AVM_ERRNO_OUTOFMEM      ((AVM_MASK_FATAL     | AVM_MASK_MEMORY   | AVM_MASK_HEAP     ) + 0x00)     // out of memory during allocation or VM initialization
#define AVM_ERRNO_SEGMNFLT      ((AVM_MASK_FATAL     | AVM_MASK_MEMORY   | AVM_MASK_HEAP     ) + 0x00)     // segmentation fault
#define AVM_ERRNO_OVERFLOW      ((AVM_MASK_FATAL     | AVM_MASK_MEMORY   | AVM_MASK_STACK    ) + 0x00)     // stack overflow
#define AVM_ERRNO_UNDRFLOW      ((AVM_MASK_FATAL     | AVM_MASK_MEMORY   | AVM_MASK_STACK    ) + 0xF0)     // stack underflow
#define AVM_ERRNO_UNREGOPC      ((AVM_MASK_FATAL     | AVM_MASK_CODE     | AVM_MASK_BCODE    ) + 0x00)     // unrecognized opcode
#define AVM_ERRNO_BCODEEOF      ((AVM_MASK_FATAL     | AVM_MASK_CODE     | AVM_MASK_BCODE    ) + 0x00)     // unexpected byte code EOF
#define AVM_ERRNO_BCINVLPC      ((AVM_MASK_FATAL     | AVM_MASK_CODE     | AVM_MASK_BCODE    ) + 0x00)     // invalid PC for byte code set

void AVM_abort(char* msg, AVM_u32 errno);

#endif /* ERROR_H_ */
