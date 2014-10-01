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

struct AVM_native
{
    char* name;
};

struct AVM_native* AVM_native_new(char* name);
void AVM_native_free(struct AVM_native* native);

void AVM_native_invoke(struct AVM_native* native, struct AVM_ABY* aby);

#endif /* NATIVE_H_ */
