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

#include "aby.h"

int main(int argc, char** argv)
{
    FILE* abyfile = fopen("../aspelc/test.aby", "rb");
    struct AVM_ABY* aby = AVM_ABY_new(abyfile);
    fclose(abyfile);

    AVM_ABY_execute(aby);

    AVM_ABY_free(aby);

    return EXIT_SUCCESS;
}
