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
 * File: native.h
 * Description: 
 * Author: Lovro Kalinovcic
 * 
 */

#ifndef NATIVE_H_
#define NATIVE_H_

#include "aby.h"

#include <stdlib.h>
#include <stdio.h>

typedef void (*AVM_native_proto)(void*);

struct AVM_native
{
    char* name;
    AVM_native_proto cfunc;
};

struct AVM_nativelib
{
    void* handle;
    struct AVM_nativelib* next;
};

struct AVM_native* AVM_native_new(char* name);
void AVM_native_free(struct AVM_native* native);

struct AVM_nativelib* AVM_nativelib_new(char* name);
void AVM_nativelib_free(struct AVM_nativelib* lib);

void AVM_nativelib_open(struct AVM_nativelib* lib, char* path);
void AVM_nativelib_close(struct AVM_nativelib* lib);

AVM_native_proto AVM_nativelib_load(struct AVM_nativelib* lib, char* symbol);

#endif /* NATIVE_H_ */
