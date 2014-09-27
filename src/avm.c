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
 * File: avm.c
 * Description: 
 * Author: Lovro Kalinovcic
 * 
 */

#include <stdlib.h>
#include <stdio.h>

#include "atype.h"
#include "stack.h"

int main(int argc, char** argv)
{
    struct AVM_stack* stack = AVM_stack_new(1024);

    AVM_u32 src = 2642;
    AVM_u32 res;

    AVM_stack_push(stack, &src, 4);
    AVM_stack_pop(stack, &res, 4);

    printf("%d\n", res);

    AVM_stack_free(stack);

    return EXIT_SUCCESS;
}
